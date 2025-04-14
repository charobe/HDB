// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HDBStructType.generated.h"

class UHDBPlayerLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FHDBPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UHDBPlayerLinkedAnimLayer> WeaponAnimLayerToLink;
};