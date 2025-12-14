// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/HDBGameplayAbility.h"
#include "EnemyGameplayAbility.generated.h"

class AHDBEnemyCharacter;
class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class HDB_MULTI_API UEnemyGameplayAbility : public UHDBGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	AHDBEnemyCharacter* GetEnemyCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);


private:
	TWeakObjectPtr<AHDBEnemyCharacter> CachedEnemyCharacter;

};
