// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_CatchFootprint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"

UBTTask_CatchFootprint::UBTTask_CatchFootprint() {
    NodeName = "Check Ground Material";
}

EBTNodeResult::Type UBTTask_CatchFootprint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn) return EBTNodeResult::Failed;

    if (IsOnFootprint(AIPawn))
    {
        return EBTNodeResult::Failed; 
    }

    return EBTNodeResult::Succeeded;


}

/*
FColor UBTTask_CatchFootprint::GetColorAtLocation(UTextureRenderTarget2D* RenderTarget, FVector WorldLocation, APlayerController* PlayerController)
{
    if (!RenderTarget || !PlayerController) return FColor::Black;

    FVector2D ScreenLocation;
    PlayerController->ProjectWorldLocationToScreen(WorldLocation, ScreenLocation);

    FRenderTarget* RenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
    FColor PixelColor;

    if (RenderTargetResource)
    {
        RenderTargetResource->ReadPixels(TArray<FColor>(), FReadSurfaceDataFlags(), PixelColor);
    }

    return PixelColor;
}
*/

bool UBTTask_CatchFootprint::IsOnFootprint(AActor* Actor)
{
    if (!Actor) return false;

    FHitResult HitResult;
    FVector Start = Actor->GetActorLocation();
    FVector End = Start - FVector(0, 0, 500);

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Actor);

    if (Actor->GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
    {
        UMaterialInterface* HitMaterial = HitResult.Component->GetMaterial(0);
        /*if (HitMaterial && HitMaterial->GetName().Contains("M_Road"))
        {
            return true;
        }*/
    }

    return false;

}