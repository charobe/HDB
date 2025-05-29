// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PlayerAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "HDBFunctionLibrary.h"
#include "Tag/HDBGameplayTag.h"
#include "Interface/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/PlayerUIComponent.h"

#include "HDBDebugHelper.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentHaza(1.f);
	InitMaxHaza(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s 는 UI Interface를 구현하지 않았습니다."), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	
	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetUIComponent();

	checkf(PawnUIComponent, TEXT("%s에서 PawnUIComponent를 불러오지 못했습니다."), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());


	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentHazaAttribute())
	{
		const float NewCurrentHaza = FMath::Clamp(GetCurrentHaza(), 0.f, GetMaxHaza());
		
		SetCurrentHaza(NewCurrentHaza);

		if (UPlayerUIComponent* PlayerUIComponent = CachedPawnUIInterface->GetPlayerUIComponent())
		{
			PlayerUIComponent->OnCurrentHazaChanged.Broadcast(GetCurrentHaza() / GetMaxHaza());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		
		SetCurrentHealth(NewCurrentHealth);
		const FString DebugString = FString::Printf(
			TEXT("기존 체력: %f, 데미지: %f, 최종 체력: %f"),
			OldHealth, DamageDone, NewCurrentHealth
		);
		//Debug::Print(DebugString, FColor::Green);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() == 0.f)
		{
			UHDBFunctionLibrary::AddGameplayTagToActor(Data.Target.GetAvatarActor(), HDBGameplayTags::Shared_Status_Death);
		}
	}
}
