// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class AHDBWeaponBase;
/**
 * 
 */
UCLASS()
class HDB_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category = "HDB|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToResiter,AHDBWeaponBase* InWeaponToResiter, bool bResgiterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "HDB|Combat")
	AHDBWeaponBase* GetCharacterOwnedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "HDB|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "HDB|Combat")
	AHDBWeaponBase* GetCharacterCurrentEquippedWeapon() const;
private:
	TMap<FGameplayTag, AHDBWeaponBase*> CharacterOwnedWeaponMap;
};
