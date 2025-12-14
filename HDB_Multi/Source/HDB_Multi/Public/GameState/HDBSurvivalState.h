// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameState/HDBGameState.h"
#include "HDBSurvivalState.generated.h"

/**
 * 
 */

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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnSurvivalStateChanged,
	EHDBSurvialGameModeState,
	NewState
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnSurvivalWaveChanged,
	int32, CurrentWaveIndex,
	int32, TotalWaves
);

UCLASS()
class HDB_MULTI_API AHDBSurvivalState : public AHDBGameState
{
	GENERATED_BODY()

public:
	AHDBSurvivalState();

	void ServerSetState(EHDBSurvialGameModeState NewState);
	void ServerSetWaveInfo(int32 NewCurrentWaveIndex, int32 NewTotalWaves);

	UFUNCTION(BlueprintPure)
	EHDBSurvialGameModeState GetCurrentState() const { return CurrentState; }

	UFUNCTION(BlueprintPure)
	int32 GetCurrentWaveCount() const { return CurrentWaveCount; }

	UFUNCTION(BlueprintPure)
	int32 GetTotalWaves() const { return TotalWaves; }

	UPROPERTY(BlueprintAssignable, Category = "Survival")
	FOnSurvivalStateChanged OnSurvivalStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "Survival")
	FOnSurvivalWaveChanged OnSurvivalWaveChanged;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentState)
	EHDBSurvialGameModeState CurrentState = EHDBSurvialGameModeState::WaitSpawnNewWave;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"), ReplicatedUsing = OnRep_WaveInfo)
	int32 CurrentWaveCount = 1;

	UPROPERTY(Replicated)
	int32 TotalWaves = 0;

	UFUNCTION()
	void OnRep_CurrentState();

	UFUNCTION()
	void OnRep_WaveInfo();

};
