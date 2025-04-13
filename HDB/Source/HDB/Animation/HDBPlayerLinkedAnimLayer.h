// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/HDBBaseAnimInstance.h"
#include "HDBPlayerLinkedAnimLayer.generated.h"

class UHDBPlayerAnimInstance;
/**
 * 
 */
UCLASS()
class HDB_API UHDBPlayerLinkedAnimLayer : public UHDBBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UHDBPlayerAnimInstance* GetPlayerAnimInstance() const;
};
