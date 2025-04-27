// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsTargetFootprint.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API UBTDecorator_IsTargetFootprint : public UBTDecorator
{

    GENERATED_BODY()

public:
    UBTDecorator_IsTargetFootprint();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    struct FBlackboardKeySelector TargetLocationKey;
	
};
