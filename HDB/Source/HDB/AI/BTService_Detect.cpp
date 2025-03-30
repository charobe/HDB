// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"
#include "AIController.h"
#include "Interface/HDBSpiderAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"
#include "Components/BoxComponent.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World)
	{
		return;
	}

	IHDBSpiderAIInterface* AIPawn = Cast<IHDBSpiderAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return;
	}

	float DetectRadius = AIPawn->GetAIDetectRange();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECC_GameTraceChannel1,		
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
			/*
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Pawn);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f, FColor::Green, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Pawn->GetActorLocation(), FColor::Green, false, 0.27f);
				return;
			}*/
			UBoxComponent* TargetComponent = Pawn->GetComponentByClass<UBoxComponent>();
			if (TargetComponent)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetComponent"), TargetComponent);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, TargetComponent->GetComponentLocation(), 10.0f, FColor::Green, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), TargetComponent->GetComponentLocation(), FColor::Green, false, 0.27f);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}


