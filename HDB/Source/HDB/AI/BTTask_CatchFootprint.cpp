// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_CatchFootprint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"

UBTTask_CatchFootprint::UBTTask_CatchFootprint() {
    NodeName = "Check Ground Material";
}

EBTNodeResult::Type UBTTask_CatchFootprint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn) return EBTNodeResult::Failed;

    if (IsOnFootprint(AIPawn, OwnerComp))
    {
        UE_LOG(LogTemp, Warning, TEXT("Catch"));

        return EBTNodeResult::Succeeded;
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("No Catch"));

        return EBTNodeResult::Failed;
    }


}


bool UBTTask_CatchFootprint::IsOnFootprint(AActor* Actor, UBehaviorTreeComponent& OwnerComp)
{
    const FVector StartLocation = Actor->GetActorLocation();
    const FVector ForwardVector = Actor->GetActorForwardVector();

    const float ScanDistance = 300; // 5m
    const float AngleRange = 30;
    const int RayCount = 20;

    UWorld* World = Actor->GetWorld();
    if (!World) return false;

    for (int i = -RayCount / 2; i <= RayCount / 2; ++i) {
        float AngleDeg = i * (AngleRange / (RayCount / 2));
        FRotator RotOffset(0, AngleDeg, 0);
        FVector Dir = RotOffset.RotateVector(ForwardVector).GetSafeNormal();
        FVector End = StartLocation + Dir * ScanDistance;

        FVector RayStart = End;
        FVector RayEnd = End - FVector(0, 0, 100);

        FHitResult HitResult;
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(Actor);

        bool bHit = World->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_Visibility, Params);

        DrawDebugLine(World, RayStart, RayEnd, FColor::Green, false, 0.5f, 0, 1.0f);
        //UE_LOG(LogTemp, Warning, TEXT("Draw Debug"));

        if (bHit)
        {
            UMaterialInterface* HitMat = HitResult.Component->GetMaterial(0);
            return true;

            if (HitMat && HitMat->GetName().Contains(TEXT("MI_Powdered_Coal_And_Soil_vbzoecbdy_2K"))) { //check metirial
                UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
                if (BlackboardComp) {
                    DrawDebugLine(World, RayStart, RayEnd, FColor::Red, false, 0.5f, 0, 1.0f);
                    BlackboardComp->SetValueAsVector(TEXT("TargetLocation"), HitResult.Location);
                }
                return true;

            }
        }
        else {
            DrawDebugLine(World, RayStart, RayEnd, FColor::Green, false, 0.5f, 0, 1.0f);
        }

    }


    return false;

}