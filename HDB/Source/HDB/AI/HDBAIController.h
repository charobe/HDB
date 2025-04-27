// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HDBAIController.generated.h"

UCLASS()
class HDB_API AHDBAIController : public AAIController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, Category = "AI")
    class UBehaviorTree* BehaviorTreeAsset;
};
