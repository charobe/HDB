// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "HDBStructType.generated.h"

class UHDBPlayerLinkedAnimLayer;
class UHDBGameplayAbility;

USTRUCT(BlueprintType)
struct FHDBPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UHDBPlayerLinkedAnimLayer> WeaponAnimLayerToLink;
};

USTRUCT(BlueprintType)
struct FHDBPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHDBGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};