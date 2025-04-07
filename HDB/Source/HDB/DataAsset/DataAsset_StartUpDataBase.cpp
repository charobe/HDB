// Fill out your copyright notice in the Description page of Project Settings.

#include "DataAsset/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/PlayerAbilitySystemComponent.h"
#include "AbilitySystem/Ability/HDBGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UPlayerAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UHDBGameplayAbility>>& InAbilitiesToGive, UPlayerAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}
	for (const TSubclassOf<UHDBGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
