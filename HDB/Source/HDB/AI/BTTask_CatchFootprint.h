// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CatchFootprint.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API UBTTask_CatchFootprint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_CatchFootprint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	//FColor GetColorAtLocation(UTextureRenderTarget2D* RenderTarget, FVector WorldLocation, APlayerController* PlayerController);

	bool IsOnFootprint(AActor* Actor);
	
};
