// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BTService_CatchFootprint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Character/FootprintManager.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"

UBTService_CatchFootprint::UBTService_CatchFootprint()
{
	NodeName = TEXT("Catch Footprint Service");
	Interval = 0.2f;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTService_CatchFootprint::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent())
	{
		BB->ClearValue(GetSelectedBlackboardKey());
	}
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}

void UBTService_CatchFootprint::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent())
	{
		BB->ClearValue(GetSelectedBlackboardKey());
	}
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}

void UBTService_CatchFootprint::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return;

	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn) return;

	FVector TargetLocation;
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return;

	if (FindBestFootprint(AIPawn, TargetLocation))
	{
		if (bProjectToNav)
		{
			if (UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIPawn))
			{
				FNavLocation Projected;
				if (NavSys->ProjectPointToNavigation(TargetLocation, Projected))
				{
					BB->SetValueAsVector(GetSelectedBlackboardKey(), Projected.Location);

					if (bDebugDraw)
					{
						DrawDebugSphere(AIPawn->GetWorld(), Projected.Location, 20.f, 12, FColor::Blue, false, Interval);
					}
				}
				else
				{
					BB->ClearValue(GetSelectedBlackboardKey());
				}
			}
			else
			{
				BB->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);
			}
		}
		else
		{
			BB->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);

			if (bDebugDraw)
			{
				DrawDebugSphere(AIPawn->GetWorld(), TargetLocation, 20.f, 12, FColor::Blue, false, Interval);
			}
		}
	}
	else
	{
		BB->ClearValue(GetSelectedBlackboardKey());
	}
}

bool UBTService_CatchFootprint::FindBestFootprint(AActor* OwnerActor, FVector& OutLocation) const
{
	if (!OwnerActor) return false;

	UWorld* World = OwnerActor->GetWorld();
	if (!World) return false;

	UFootprintManager* Manager = UFootprintManager::Get(World);
	if (!Manager) return false;

	const float CurrentTime = World->GetTimeSeconds();
	const TArray<FVector> Footprints = Manager->GetActiveFootprintLocations(CurrentTime, MaxLifetimeSec);
	if (Footprints.Num() == 0) return false;

	const FVector StartLocation = OwnerActor->GetActorLocation();
	const FVector Fwd2D = OwnerActor->GetActorForwardVector().GetSafeNormal2D();

	const float DotThreshold = bUseAngleCheck ? FMath::Cos(FMath::DegreesToRadians(AngleRangeDeg)) : -1.f;

	float BestScore = bPickNearest ? TNumericLimits<float>::Max() : -1.f;
	bool bFound = false;

	for (const FVector& FP : Footprints)
	{
		const FVector ToFP = FP - StartLocation;
		const float Dist2D = ToFP.Size2D();
		if (Dist2D > ScanDistance) continue;

		if (bUseAngleCheck)
		{
			const float Dot = FMath::Clamp(FVector::DotProduct(Fwd2D, ToFP.GetSafeNormal2D()), -1.f, 1.f);
			if (Dot < DotThreshold) continue;
		}

		if (bPickNearest)
		{
			if (Dist2D < BestScore)
			{
				BestScore = Dist2D;
				OutLocation = FP;
				bFound = true;
			}
		}
		else
		{
			if (Dist2D > BestScore)
			{
				BestScore = Dist2D;
				OutLocation = FP;
				bFound = true;
			}
		}
	}

	return bFound;
}

