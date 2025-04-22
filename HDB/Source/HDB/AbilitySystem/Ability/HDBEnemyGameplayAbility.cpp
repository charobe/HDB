// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/HDBEnemyGameplayAbility.h"
#include "Character/HDBEnemyCharacter.h"


AHDBEnemyCharacter* UHDBEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<AHDBEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UHDBEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
