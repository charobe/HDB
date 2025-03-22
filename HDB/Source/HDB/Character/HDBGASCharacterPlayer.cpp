// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBGASCharacterPlayer.h"
#include "AbilitySystemComponent.h"
#include "Player/HDBGASPlayerState.h"

AHDBGASCharacterPlayer::AHDBGASCharacterPlayer()
{
	ASC = nullptr;
}


UAbilitySystemComponent* AHDBGASCharacterPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

void AHDBGASCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AHDBGASPlayerState* GASPS = GetPlayerState<AHDBGASPlayerState>();
	if (GASPS)
	{
		ASC = GASPS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(GASPS, this);

		for (const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			ASC->GiveAbility(StartSpec);
		}
	}
}
