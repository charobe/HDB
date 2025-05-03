// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_CatchFootprint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Footprint/FootprintManager.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_CatchFootprint::UBTTask_CatchFootprint() {
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
        UE_LOG(LogTemp, Warning, TEXT("Footprint!"));
        return EBTNodeResult::Succeeded;
    }

    UE_LOG(LogTemp, Warning, TEXT("No footprint"));
    return EBTNodeResult::Failed;
}


bool UBTTask_CatchFootprint::IsFootprintInSight(AActor* Actor, UBehaviorTreeComponent& OwnerComp)
{
    const FVector StartLocation = Actor->GetActorLocation();
    const FVector ForwardVector = Actor->GetActorForwardVector();

    const float ScanDistance = 500.f;
    const float AngleRange = 30.f;
    const float XYThreshold = 50.f;

    UWorld* World = Actor->GetWorld();
    if (!World) return false;

    const float CurrentTime = World->GetTimeSeconds();
    const float MaxLifetime = 5.f;

    TArray<FVector> Footprints = UFootprintManager::Get(World)->GetActiveFootprintLocations(CurrentTime, MaxLifetime);

    for (const FVector& Footprint : Footprints)
    {
        FVector DirectionToFootprint = (Footprint - StartLocation).GetSafeNormal2D();
        float Dot = FVector::DotProduct(ForwardVector.GetSafeNormal2D(), DirectionToFootprint);
        float AngleDeg = FMath::RadiansToDegrees(FMath::Acos(Dot));

        float Distance = FVector::Dist2D(StartLocation, Footprint);

        if (AngleDeg <= AngleRange && Distance <= ScanDistance)
        {
            if (FMath::Abs(Footprint.X - StartLocation.X) <= ScanDistance &&
                FMath::Abs(Footprint.Y - StartLocation.Y) <= ScanDistance)
            {
                UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
                if (Blackboard)
                {
                    Blackboard->SetValueAsVector(TEXT("TargetLocation"), Footprint);
                    DrawDebugSphere(World, Footprint, 20.f, 12, FColor::Red, false, 1.0f);
                }

                return true;
            }
        }
    }

    return false;
}