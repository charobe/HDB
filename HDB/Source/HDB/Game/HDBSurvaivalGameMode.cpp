#include "Game/HDBSurvaivalGameMode.h"

void AHDBSurvaivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("유효한 데이터 테이블이 존재하지 않음"));

	SetCurrentSurvivalGameModeState(EHDBSurvivalGameModeState::WaitSpawnNewWave);

	TotalWave= EnemyWaveSpawnerDataTable->GetRowNames().Num();

}

void AHDBSurvaivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentSurvivalGameModeState == EHDBSurvivalGameModeState::WaitSpawnNewWave)
	{
		elapsedTime += DeltaTime;
		
		if (elapsedTime >= SpawnWaitTime)
		{
			elapsedTime = 0.f;

			SetCurrentSurvivalGameModeState(EHDBSurvivalGameModeState::SpawningNewWave);
		}
	}

	if (CurrentSurvivalGameModeState == EHDBSurvivalGameModeState::SpawningNewWave)
	{
		elapsedTime += DeltaTime;

		if (elapsedTime >= SpawnDelayTime)
		{
			elapsedTime = 0.f;

			SetCurrentSurvivalGameModeState(EHDBSurvivalGameModeState::InProgress);

		}
	}

	if (CurrentSurvivalGameModeState == EHDBSurvivalGameModeState::WaveCompleted)
	{
		elapsedTime += DeltaTime;

		if (elapsedTime >= WaveCompletedWaitTime)
		{
			elapsedTime = 0.f;

			CurrentWaveCount++;

			if (HasFinishedAllWave())
			{
				SetCurrentSurvivalGameModeState(EHDBSurvivalGameModeState::AllWavesDone);
			}
			else
			{
				SetCurrentSurvivalGameModeState(EHDBSurvivalGameModeState::WaitSpawnNewWave);
			}
		}
	}
}

void AHDBSurvaivalGameMode::SetCurrentSurvivalGameModeState(EHDBSurvivalGameModeState State)
{
	CurrentSurvivalGameModeState = State;

	OnSurvivalGameModeStateChanged.Broadcast(CurrentSurvivalGameModeState);
}

bool AHDBSurvaivalGameMode::HasFinishedAllWave() const
{
	return CurrentWaveCount >= TotalWave;
}
