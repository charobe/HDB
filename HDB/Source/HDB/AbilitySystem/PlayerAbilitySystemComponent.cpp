// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/PlayerAbilitySystemComponent.h"
#include "AbilitySystem/Ability/HDBGameplayAbility.h"


void UPlayerAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			continue;
		}
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UPlayerAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}

void UPlayerAbilitySystemComponent::GrantPlayerWeaponAbilities(const TArray<FHDBPlayerAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FHDBPlayerAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		GiveAbility(AbilitySpec);
	}
}
