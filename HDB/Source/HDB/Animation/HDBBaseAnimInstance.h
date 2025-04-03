// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HDBBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API UHDBBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

protected:
	UPROPERTY()
	TObjectPtr<class AHDBCharacterPlayer> OwningCharacter;

	UPROPERTY()
	TObjectPtr<class UCharacterMovementComponent> OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category="AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;
};
