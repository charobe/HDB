// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CatchFootprint.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API UBTService_CatchFootprint : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_CatchFootprint();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool FindFarthestFootprint(AActor* OwnerActor, FVector& OutLocation);
	
};
