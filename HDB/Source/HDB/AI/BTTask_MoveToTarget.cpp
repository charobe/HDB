// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_MoveToTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/Character.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
    NodeName = "Move To Target Location";
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    CachedOwnerComp = &OwnerComp;
    CachedAIController = OwnerComp.GetAIOwner();

    if (!CachedAIController) return EBTNodeResult::Failed;

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp) return EBTNodeResult::Failed;

    FVector TargetLocation = BlackboardComp->GetValueAsVector(TargetLocationKey.SelectedKeyName);

    if (TargetLocation.IsNearlyZero())
    {
        UE_LOG(LogTemp, Warning, TEXT("TargetLocation is Zero"));
        return EBTNodeResult::Failed;
    }



    FAIRequestID MoveRequestID = CachedAIController->MoveToLocation(TargetLocation);

    if (!MoveRequestID.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveToLocation Failed"));
        return EBTNodeResult::Failed;
    }

    if (CachedAIController->GetPathFollowingComponent())
    {
        MoveCompleteDelegateHandle = CachedAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &UBTTask_MoveToTarget::HandleMoveCompleted);
    }

    UE_LOG(LogTemp, Warning, TEXT("Moving to Target Location..."));
    return EBTNodeResult::InProgress;
}

void UBTTask_MoveToTarget::HandleMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (!CachedOwnerComp || !CachedAIController)
    {
        return;
    }

    if (CachedAIController->GetPathFollowingComponent())
    {
        CachedAIController->GetPathFollowingComponent()->OnRequestFinished.Remove(MoveCompleteDelegateHandle);
    }

    if (Result.IsSuccess())
    {
        UE_LOG(LogTemp, Warning, TEXT("Move Completed Successfully!"));
        FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Move Failed!"));
        FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Failed);
    }
}