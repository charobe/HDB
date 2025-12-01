// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/BTTask_MoveToTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
    NodeName = TEXT("Move To Target Location");

    TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_MoveToTarget, TargetLocationKey));

    bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    CachedOwnerComp = &OwnerComp;
    CachedAIController = OwnerComp.GetAIOwner();
    if (!CachedAIController) return EBTNodeResult::Failed;

    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (!BB) return EBTNodeResult::Failed;

    if (!BB->IsVectorValueSet(TargetLocationKey.SelectedKeyName))
    {
        UE_LOG(LogTemp, Warning, TEXT("TargetLocation is NOT set on Blackboard"));
        return EBTNodeResult::Failed;
    }

    const FVector TargetLocation = BB->GetValueAsVector(TargetLocationKey.SelectedKeyName);

    FNavLocation Projected;
    if (UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(CachedAIController))
    {
        if (!NavSys->ProjectPointToNavigation(TargetLocation, Projected))
        {
            UE_LOG(LogTemp, Warning, TEXT("TargetLocation is off the NavMesh"));
            return EBTNodeResult::Failed;
        }
    }

    const EPathFollowingRequestResult::Type Req =
        CachedAIController->MoveToLocation(TargetLocation, 50.f, true);

    if (Req == EPathFollowingRequestResult::Failed)
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveToLocation request failed"));
        return EBTNodeResult::Failed;
    }

    if (auto* PFC = CachedAIController->GetPathFollowingComponent())
    {
        MoveCompleteDelegateHandle =
            PFC->OnRequestFinished.AddUObject(this, &UBTTask_MoveToTarget::HandleMoveCompleted);
    }

    UE_LOG(LogTemp, Log, TEXT("Moving to Target Location..."));
    return EBTNodeResult::InProgress;
}

void UBTTask_MoveToTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    if (CachedAIController && CachedAIController->GetPathFollowingComponent())
    {
        CachedAIController->GetPathFollowingComponent()->OnRequestFinished.Remove(MoveCompleteDelegateHandle);
    }
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}

void UBTTask_MoveToTarget::HandleMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (!CachedOwnerComp || !CachedAIController) return;

    if (CachedAIController->GetPathFollowingComponent())
    {
        CachedAIController->GetPathFollowingComponent()->OnRequestFinished.Remove(MoveCompleteDelegateHandle);
    }

    if (Result.IsSuccess())
    {
        UE_LOG(LogTemp, Log, TEXT("Move Completed Successfully!"));
        FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Move Failed: %s"), *UEnum::GetValueAsString(Result.Code));
        FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Failed);
    }
}
