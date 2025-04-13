// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/HDBPlayerGameplayAbility.h"
#include "Character/HDBCharacterPlayer.h"
#include "Player/HDBPlayerController.h"


AHDBCharacterPlayer* UHDBPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
    if (!CachedPlayerCharacter.IsValid())
    {
        CachedPlayerCharacter= Cast<AHDBCharacterPlayer>(CurrentActorInfo->AvatarActor);
    }
    return CachedPlayerCharacter.IsValid()? CachedPlayerCharacter.Get() : nullptr;
}

AHDBPlayerController* UHDBPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
    if (!CachedPlayerController.IsValid())
    {
        CachedPlayerController = Cast<AHDBPlayerController>(CurrentActorInfo->PlayerController);
    }

    return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;

}

UPlayerCombatComponent* UHDBPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
    return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}
