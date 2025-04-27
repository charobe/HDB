// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnCombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class AHDBPlayerWeapon;

/**
 * 
 */
UCLASS()
class HDB_API UPlayerCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "HDB|Combat")
	AHDBPlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;

	virtual void OnWeaponPulledTargetActor(AActor* InteractedActor) override;

};
