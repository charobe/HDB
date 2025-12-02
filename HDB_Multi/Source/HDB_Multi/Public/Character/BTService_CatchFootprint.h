// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CatchFootprint.generated.h"

/**
 * 
 */
UCLASS()
class HDB_MULTI_API UBTService_CatchFootprint : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_CatchFootprint();

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// ÁÖ±â ½ºÄµ
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool FindBestFootprint(AActor* OwnerActor, FVector& OutLocation) const;

public:
	UPROPERTY(EditAnywhere, Category = "CatchFootprint", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ScanDistance = 500.f;

	UPROPERTY(EditAnywhere, Category = "CatchFootprint", meta = (ClampMin = "0.0", ClampMax = "180.0", UIMin = "0.0", UIMax = "180.0"))
	float AngleRangeDeg = 70.f;

	UPROPERTY(EditAnywhere, Category = "CatchFootprint", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxLifetimeSec = 5.0f;

	UPROPERTY(EditAnywhere, Category = "CatchFootprint")
	bool bUseAngleCheck = true;

	UPROPERTY(EditAnywhere, Category = "CatchFootprint")
	bool bPickNearest = false;

	UPROPERTY(EditAnywhere, Category = "CatchFootprint")
	bool bProjectToNav = true;

	UPROPERTY(EditAnywhere, Category = "CatchFootprint")
	bool bDebugDraw = false;
};
