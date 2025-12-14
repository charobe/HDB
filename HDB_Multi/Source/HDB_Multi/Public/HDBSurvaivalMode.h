// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HDBGameModeBase.h"
#include "HDBSurvaivalMode.generated.h"


UENUM(BlueprintType)
enum class EHDBSurvialGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesDone,
	PlayerDied
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvialGameModeStateChangedDelegate, EHDBSurvialGameModeState, CurrentState);
/**
 * 
 */
UCLASS()
class HDB_MULTI_API AHDBSurvaivalMode : public AHDBGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetCurrentSurvialGameModeState(EHDBSurvialGameModeState InState);

	UPROPERTY()
	EHDBSurvialGameModeState CurrentSurvialGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvialGameModeStateChangedDelegate OnSurvialGameModeStateChanged;
};
