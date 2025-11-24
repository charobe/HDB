// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/HDBCharacterAnimInstance.h"
#include "HDBPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HDB_MULTI_API UHDBPlayerAnimInstance : public UHDBCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
