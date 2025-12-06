// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnComponentBase.h"
#include "PawnCombatComponent.generated.h"

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	LeftHand,
	RightHand
};

/**
 * 
 */
UCLASS()
class HDB_MULTI_API UPawnCombatComponent : public UPawnComponentBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "HDB|Combat")
	void ToggleCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);

};
