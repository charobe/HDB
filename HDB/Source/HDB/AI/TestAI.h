// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TestAI.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API ATestAI : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTreeAsset;
	
};
