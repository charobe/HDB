// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/HDBGameplayAbility.h"
#include "HDBEnemyGameplayAbility.generated.h"

class AHDBEnemyCharacter;
class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class HDB_API UHDBEnemyGameplayAbility : public UHDBGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	AHDBEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AHDBEnemyCharacter> CachedEnemyCharacter;
};
