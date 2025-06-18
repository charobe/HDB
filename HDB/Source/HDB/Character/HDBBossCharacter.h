// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HDBEnemyCharacter.h"
#include "HDBBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API AHDBBossCharacter : public AHDBEnemyCharacter
{
	GENERATED_BODY()
public:
	AHDBBossCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UMaterialInstanceDynamic* DeformMaterial;

	FVector ImpactLocation;
	float ImpactStrength = 0.f;
	float ImpactRadius = 30.f;
	float TimeSinceImpact = 0.f;
	float RecoveryDuration = 1.5f;
	bool bDeforming = false;
	
};
