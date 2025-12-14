// Fill out your copyright notice in the Description page of Project Settings.


#include "HDBSurvaivalMode.h"
#include "GameState/HDBSurvivalState.h"


AHDBSurvaivalMode::AHDBSurvaivalMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	GameStateClass = AHDBSurvivalState::StaticClass();

}

void AHDBSurvaivalMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a valid datat table in survial game mode blueprint"));

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();

	if (AHDBSurvivalState* GS = GetGameState<AHDBSurvivalState>())
	{
		GS->ServerSetWaveInfo(CurrentWaveCount, TotalWavesToSpawn);
	}

	SetCurrentSurvialGameModeState(EHDBSurvialGameModeState::WaitSpawnNewWave);
}

void AHDBSurvaivalMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentSurvialGameModeState)
	{
	case EHDBSurvialGameModeState::WaitSpawnNewWave:
	{
		TimePassedSinceStart += DeltaTime;
		if (TimePassedSinceStart >= SpawnNewWaveWaitTime)
		{
			SetCurrentSurvialGameModeState(EHDBSurvialGameModeState::SpawningNewWave);
		}
		break;
	}
	case EHDBSurvialGameModeState::SpawningNewWave:
	{
		TimePassedSinceStart += DeltaTime;
		if (TimePassedSinceStart >= SpawnEnemiesDelayTime)
		{
			SetCurrentSurvialGameModeState(EHDBSurvialGameModeState::InProgress);
		}
		break;
	}
	case EHDBSurvialGameModeState::WaveCompleted:
	{
		TimePassedSinceStart += DeltaTime;
		if (TimePassedSinceStart >= WaveCompletedWaitTime)
		{
			CurrentWaveCount++;

			if (AHDBSurvivalState* GS = GetGameState<AHDBSurvivalState>())
			{
				GS->ServerSetWaveInfo(CurrentWaveCount, TotalWavesToSpawn);
			}

			if (HasFinishedAllWaves())
			{
				SetCurrentSurvialGameModeState(EHDBSurvialGameModeState::AllWavesDone);
			}
			else
			{
				SetCurrentSurvialGameModeState(EHDBSurvialGameModeState::WaitSpawnNewWave);
			}
		}
		break;
	}

	default:
		break;
	}
}

void AHDBSurvaivalMode::SetCurrentSurvialGameModeState(EHDBSurvialGameModeState InState)
{
	if (CurrentSurvialGameModeState == InState)
	{
		return;
	}

	CurrentSurvialGameModeState = InState;

	TimePassedSinceStart = 0.f;

	if (AHDBSurvivalState* GS = GetGameState<AHDBSurvivalState>())
	{
		GS->ServerSetState(CurrentSurvialGameModeState);
	}
}

bool AHDBSurvaivalMode::HasFinishedAllWaves() const
{
	return CurrentWaveCount > TotalWavesToSpawn;
}
