// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CatchFootprint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Footprint/FootprintManager.h"
#include "DrawDebugHelpers.h"

UBTService_CatchFootprint::UBTService_CatchFootprint()
{
    NodeName = "Catch Footprint Service";
    Interval = 0.2f;
    bNotifyBecomeRelevant = true;
}

void UBTService_CatchFootprint::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return;

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn) return;

    FVector TargetLocation;
    if (FindFarthestFootprint(AIPawn, TargetLocation))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);
        //DrawDebugSphere(AIPawn->GetWorld(), TargetLocation, 20.f, 12, FColor::Blue, false, 1.f);
    }
}

bool UBTService_CatchFootprint::FindFarthestFootprint(AActor* Actor, FVector& OutLocation)
{
    const FVector StartLocation = Actor->GetActorLocation();
    const FVector ForwardVector = Actor->GetActorForwardVector();

    const float ScanDistance = 500.f;
    const float AngleRange = 70.f;
    const float MaxLifetime = 5.0f;

    UWorld* World = Actor->GetWorld();
    if (!World) return false;

    float CurrentTime = World->GetTimeSeconds();
    TArray<FVector> Footprints = UFootprintManager::Get(World)->GetActiveFootprintLocations(CurrentTime, MaxLifetime);

    float MaxDist = -1.f;
    bool bFound = false;

    for (const FVector& FP : Footprints)
    {
        FVector DirToFP = FP - StartLocation;
        float Dist = DirToFP.Size2D();

        if (Dist > ScanDistance) continue;

        float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(
            ForwardVector.GetSafeNormal2D(),
            DirToFP.GetSafeNormal2D()
        )));

        if (Angle <= AngleRange && Dist > MaxDist)
        {
            OutLocation = FP;
            MaxDist = Dist;
            bFound = true;
        }
    }

    return bFound;
}