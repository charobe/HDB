// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveRandom.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API UBTTask_MoveRandom : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTask_MoveRandom();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere)
    float MoveDistance = 10000.0f;
	
};
