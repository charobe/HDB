// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/PlayerGameplayAbility.h"
#include "Character/HDBPlayerCharacter.h"
#include "Controller/HDBPlayerController.h"

AHDBPlayerCharacter* UPlayerGameplayAbility::GetPlayerCharacterFromActor()
{
	if (!CachedPlayerCharacter.IsValid())
	{
	
	CachedPlayerCharacter = Cast<AHDBPlayerCharacter>(CurrentActorInfo->AvatarActor);
}
	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

AHDBPlayerController* UPlayerGameplayAbility::GetPlayerControllerFromActor()
{
	if (!CachedPlayerController.IsValid())
	{

		CachedPlayerController = Cast<AHDBPlayerController>(CurrentActorInfo->AvatarActor);
	}
	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UPlayerCombatComponent* UPlayerGameplayAbility::GetPlayerCombatComponentFromActor()
{
	return GetPlayerCharacterFromActor()->GetPlayerCombatComponent();
}
