// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HDBAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class HDB_API AHDBAIController : public AAIController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, Category = "AI")
    class UBehaviorTree* BehaviorTreeAsset;

    AHDBAIController(const FObjectInitializer& ObjectInitializer);

    // IGenericTeamAgentInterface
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;


protected:
   UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
   UAIPerceptionComponent* EnemyPerceptionComponent;

   UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
   UAISenseConfig_Sight* AISenseConfig_Sight;

   UFUNCTION()
   virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);


};
