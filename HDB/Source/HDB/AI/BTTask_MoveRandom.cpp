// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MoveRandom.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MoveRandom::UBTTask_MoveRandom()
{
    NodeName = TEXT("Move In Random Direction");
}

EBTNodeResult::Type UBTTask_MoveRandom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn) return EBTNodeResult::Failed;

    FVector Origin = AIPawn->GetActorLocation();


    float RandomYaw = FMath::RandRange(0.f, 360.f);
    FRotator RandomRotator(0.f, RandomYaw, 0.f);
    FVector Direction = RandomRotator.Vector();

    FVector TargetLocation = Origin + (Direction * MoveDistance);

    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (NavSys)
    {
        FNavLocation NavLocation;
        if (NavSys->ProjectPointToNavigation(TargetLocation, NavLocation))
        {
            AIController->MoveToLocation(NavLocation.Location);
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}