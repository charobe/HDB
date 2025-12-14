// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "HDBAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class HDB_MULTI_API AHDBAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AHDBAIController(const FObjectInitializer& ObjectInitializer);

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UFUNCTION()
	void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
