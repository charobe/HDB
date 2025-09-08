// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_PlayerStartUpData.h"
#include "AbilitySystem/Ability/HDBGameplayAbility.h"
#include "AbilitySystem/PlayerAbilitySystemComponent.h"



void UDataAsset_PlayerStartUpData::GiveToAbilitySystemComponent(UPlayerAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (!InASCToGive || !InASCToGive->GetOwner() || !InASCToGive->GetOwner()->HasAuthority())
	{
		return;
	}

	for (const FHDBPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySet)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}
		TSubclassOf<UGameplayAbility> AbilityClass = AbilitySet.AbilityToGrant;
		FGameplayAbilitySpec AbilitySpec(AbilityClass, ApplyLevel, static_cast<int32>(INDEX_NONE), InASCToGive->GetAvatarActor());

		//AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		//AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
