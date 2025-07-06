// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HDBEnemyCharacter.h"
#include "GameFramework/Character.h"
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

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, Category = "Material")
	FName TargetBoneName = TEXT("GHand_R");

public:
	virtual void Tick(float DeltaTime) override;

	void ApplyImpactDeform(const FVector& HitLocation, float Strength, FName HitBoneName = NAME_None);

private:
	UPROPERTY()
	UMaterialInstanceDynamic* DeformMaterial;

	FVector ImpactLocation;
	float ImpactStrength = 0.f;
	float ImpactRadius = 30.f;
	float TimeSinceImpact = 0.f;
	float RecoveryDuration = 1.5f;
	bool bDeforming = false;

	UPROPERTY(EditAnywhere, Category = "Decal")
	UMaterialInterface* ClawMarkDecalMaterial;

	UPROPERTY(EditAnywhere, Category = "Decal")
	FVector DecalOffset = FVector(0, 0, 100);
	
};
