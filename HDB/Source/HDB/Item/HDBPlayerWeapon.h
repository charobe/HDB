// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/HDBWeaponBase.h"
#include "Type/HDBStructType.h"
#include "HDBPlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API AHDBPlayerWeapon : public AHDBWeaponBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FHDBPlayerWeaponData PlayerWeaponData;
};
