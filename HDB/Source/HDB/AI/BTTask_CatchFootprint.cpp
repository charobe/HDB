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
    const float AngleRange = 30.f;

    UWorld* World = Actor->GetWorld();
    if (!World) return false;

    const float CurrentTime = World->GetTimeSeconds();
    const float MaxLifetime = 5.f;

    UFootprintManager* FootprintManager = UFootprintManager::Get(World);
    if (!FootprintManager)
    {
        UE_LOG(LogTemp, Error, TEXT("FootprintManager is NULL!"));
        return false;
    }

    TArray<FVector> Footprints = FootprintManager->GetActiveFootprintLocations(CurrentTime, MaxLifetime);
    UE_LOG(LogTemp, Warning, TEXT("Found %d footprints."), Footprints.Num());

    for (const FVector& Footprint : Footprints)
    {
        FVector DirectionToFootprint = (Footprint - StartLocation).GetSafeNormal2D();
        float Dot = FVector::DotProduct(ForwardVector.GetSafeNormal2D(), DirectionToFootprint);
        float AngleDeg = FMath::RadiansToDegrees(FMath::Acos(Dot));

        float Distance = FVector::Dist2D(StartLocation, Footprint);

        UE_LOG(LogTemp, Warning, TEXT("Footprint at %s: Angle=%.2f, Distance=%.2f"),
            *Footprint.ToString(), AngleDeg, Distance);

        if (AngleDeg <= AngleRange && Distance <= ScanDistance)
        {
            UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
            if (Blackboard)
            {
                Blackboard->SetValueAsVector(TargetLocationKeyName, Footprint);
                DrawDebugSphere(World, Footprint, 20.f, 12, FColor::Red, false, 1.0f);
                UE_LOG(LogTemp, Warning, TEXT("Set TargetLocation to: %s"), *Footprint.ToString());
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Blackboard component is NULL!"));
            }

            return true;
        }
    }

    return false;
}