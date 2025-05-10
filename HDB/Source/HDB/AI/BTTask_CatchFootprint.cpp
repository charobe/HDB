// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_CatchFootprint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Footprint/FootprintManager.h"

const FName UBTTask_CatchFootprint::TargetLocationKeyName(TEXT("TargetLocation"));

UBTTask_CatchFootprint::UBTTask_CatchFootprint()
{
    NodeName = "Check Ground Material";
}

EBTNodeResult::Type UBTTask_CatchFootprint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn) return EBTNodeResult::Failed;

    if (IsFootprintInSight(AIPawn, OwnerComp))
    {
        UE_LOG(LogTemp, Warning, TEXT("Footprint detected and TargetLocation set."));
        return EBTNodeResult::Succeeded;
    }

    UE_LOG(LogTemp, Warning, TEXT("No footprint found."));
    return EBTNodeResult::Failed;
}

bool UBTTask_CatchFootprint::IsFootprintInSight(AActor* Actor, UBehaviorTreeComponent& OwnerComp)
{
    const FVector StartLocation = Actor->GetActorLocation();
    const FVector ForwardVector = Actor->GetActorForwardVector();

    const float ScanDistance = 500.f;
    const float AngleRange = 60.f;
    const float MaxLifetime = 7.0f;

    UWorld* World = Actor->GetWorld();
    if (!World) return false;

    float CurrentTime = World->GetTimeSeconds();
    TArray<FVector> Footprints = UFootprintManager::Get(World)->GetActiveFootprintLocations(CurrentTime, MaxLifetime);

    FVector BestTarget = FVector::ZeroVector;
    float MaxDistance = -1.f;
    bool bFound = false;

    for (const FVector& Footprint : Footprints)
    {
        FVector ToFootprint = Footprint - StartLocation;
        float Distance = ToFootprint.Size2D();

        if (Distance > ScanDistance)
            continue;

        float AngleDeg = FMath::RadiansToDegrees(
            FMath::Acos(FVector::DotProduct(ForwardVector.GetSafeNormal2D(), ToFootprint.GetSafeNormal2D()))
        );

        if (AngleDeg <= AngleRange)
        {
            if (Distance > MaxDistance)
            {
                MaxDistance = Distance;
                BestTarget = Footprint;
                bFound = true;
            }
        }
    }

    if (bFound)
    {
        UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
        if (Blackboard)
        {
            Blackboard->SetValueAsVector(TEXT("TargetLocation"), BestTarget);
            DrawDebugSphere(World, BestTarget, 20.f, 12, FColor::Blue, false, 1.0f);
        }
        return true;
    }

    return false;
}