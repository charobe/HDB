// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/HDBGameplayAbility.h"
#include "HDBPlayerGameplayAbility.generated.h"

class AHDBCharacterPlayer;
class AHDBPlayerController;
/**
 * 
 */
UCLASS()
class HDB_API UHDBPlayerGameplayAbility : public UHDBGameplayAbility
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	AHDBCharacterPlayer* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	AHDBPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCurrentComboCount);

private:
	TWeakObjectPtr<AHDBCharacterPlayer> CachedPlayerCharacter;
	TWeakObjectPtr<AHDBPlayerController> CachedPlayerController;

};
