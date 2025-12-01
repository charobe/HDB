// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation/PathFollowingComponent.h" 
#include "BTTask_MoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class HDB_MULTI_API UBTTask_MoveToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTask_MoveToTarget();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

private:
    UBehaviorTreeComponent* CachedOwnerComp = nullptr;
    AAIController* CachedAIController = nullptr;

    FDelegateHandle MoveCompleteDelegateHandle;

    void HandleMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

public:
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector TargetLocationKey;
	
};
