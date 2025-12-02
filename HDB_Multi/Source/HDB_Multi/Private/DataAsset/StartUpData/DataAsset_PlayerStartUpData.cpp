// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUpData/DataAsset_PlayerStartUpData.h"
#include "AbilitySystem/Ability/HDBGameplayAbility.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"


void UDataAsset_PlayerStartUpData::GiveToAbilitySystemComponent(UHDBAbilitySystemComponent* ASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(ASCToGive, ApplyLevel);

	const AActor* OwnerActor = ASCToGive->GetOwnerActor();
	if (!OwnerActor || !OwnerActor->HasAuthority())
	{
		return;
	}

	for (const FHDBPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)

	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = ASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		ASCToGive->GiveAbility(AbilitySpec);

	}
}
