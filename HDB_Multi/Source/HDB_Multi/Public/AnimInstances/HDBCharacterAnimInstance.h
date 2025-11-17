// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/HDBBaseAnimInstance.h"
#include "Character/HDBCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HDBCharacterAnimInstance.generated.h"


/**
 * 
 */
UCLASS()
class HDB_MULTI_API UHDBCharacterAnimInstance : public UHDBBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;           
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY()
	TObjectPtr<AHDBCharacterBase> OwningCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed = 0.f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bAcceleration = false;

};
