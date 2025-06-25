// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HDBPotionBase.h"
#include "Character/HDBCharacterPlayer.h"
#include "AbilitySystem/PlayerAbilitySystemComponent.h"
#include "Tag/HDBGameplayTag.h"

void AHDBPotionBase::Use(UPlayerAbilitySystemComponent* Component, int32 ApplyLevel)
{
	check(GameplayEffectClass);

	UGameplayEffect* CDO =  GameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	Component->ApplyGameplayEffectToSelf(
		CDO,
		ApplyLevel,
		Component->MakeEffectContext()
	);

	BP_PotionUsed();
}

void AHDBPotionBase::OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHDBCharacterPlayer* Player = Cast<AHDBCharacterPlayer>(OtherActor))
	{
		Player->GetPlayerAbilitySystemComponent()->TryActivateAbilityByTag(HDBGameplayTags::Player_Ability_Get_Potion);
	}
}
