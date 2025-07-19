// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	virtual void OnHitTargetActorWithHit(AActor* HitActor, const FHitResult& HitResult) override;

protected:
	virtual void ToggleBodyCollsionBoxCollsion(bool bShouldEnable, EToggleDamageType ToggleDamageType) override;

};
