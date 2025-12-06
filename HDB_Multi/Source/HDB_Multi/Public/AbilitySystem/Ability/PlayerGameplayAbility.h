// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/HDBGameplayAbility.h"
#include "PlayerGameplayAbility.generated.h"

class AHDBPlayerCharacter;
class AHDBPlayerController;
class UPlayerCombatComponent;
/**
 * 
 */
UCLASS()
class HDB_MULTI_API UPlayerGameplayAbility : public UHDBGameplayAbility
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	AHDBPlayerCharacter* GetPlayerCharacterFromActor();

	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	AHDBPlayerController* GetPlayerControllerFromActor();

	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponentFromActor();

	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCurrentComboCount);
private:
	TWeakObjectPtr<AHDBPlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<AHDBPlayerController> CachedPlayerController;

};
