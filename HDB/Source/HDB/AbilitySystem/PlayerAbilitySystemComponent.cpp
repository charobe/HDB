// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PlayerAbilitySystemComponent.h"

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
