// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUpData/DataAsset_EnemyStartUpData.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"
#include "AbilitySystem/Ability/EnemyGameplayAbility.h"


void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UHDBAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (!EnemyCombatAbility.IsEmpty())
	{
		for (const TSubclassOf < UEnemyGameplayAbility >& AbilityClass : EnemyCombatAbility)
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
