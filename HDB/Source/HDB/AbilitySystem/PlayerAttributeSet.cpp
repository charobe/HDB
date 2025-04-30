// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PlayerAttributeSet.h"
#include "GameplayEffectExtension.h"

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
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());

		SetCurrentHealth(NewCurrentRage);
	}

	if (Data.EvaluatedData.Attribute == GetCurrentHazaAttribute())
	{
		const float NewCurrentHaza = FMath::Clamp(GetCurrentHaza(), 0.f, GetMaxHaza());
		
		SetCurrentHealth(NewCurrentHaza);

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
		Debug::Print(DebugString, FColor::Green);
	}
}
