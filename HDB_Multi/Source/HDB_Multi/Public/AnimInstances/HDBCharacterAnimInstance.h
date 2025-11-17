// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/HDBBaseAnimInstance.h"
#include "HDBCharacterAnimInstance.generated.h"

class AHDBCharacterBase;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class HDB_MULTI_API UHDBCharacterAnimInstance : public UHDBBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY()
	AHDBCharacterBase* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bAcceleration;

};
