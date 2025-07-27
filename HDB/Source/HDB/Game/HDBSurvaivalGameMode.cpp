#include "Game/HDBSurvaivalGameMode.h"
#include "Engine/AssetManager.h"
#include "Character/HDBEnemyCharacter.h"

#include "HDBDebugHelper.h"

void AHDBSurvaivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("유효한 데이터 테이블이 존재하지 않음"));

	SetCurrentSurvivalGameModeState(EHDBSurvivalGameModeState::WaitSpawnNewWave);

	TotalWave= EnemyWaveSpawnerDataTable->GetRowNames().Num();

	PreLoadNextWave();
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
				PreLoadNextWave();
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
	return CurrentWaveCount > TotalWave;
}

void AHDBSurvaivalGameMode::PreLoadNextWave()
{
	if (HasFinishedAllWave())
	{
		return;
	}

	for (const FHDBEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.EnemyClassToSpawn.IsNull())
			continue;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.EnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[SpawnerInfo, this]()
				{
					if (UClass* EnemyClass = SpawnerInfo.EnemyClassToSpawn.Get())
					{
						PreLoadedEnemyClass.Emplace(SpawnerInfo.EnemyClassToSpawn, EnemyClass);
						Debug::Print(EnemyClass->GetName());
					
					}
				}
			)
		);
	}

}

FHDBEnemyWaveSpawnerTableRow* AHDBSurvaivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Wave") + FString::FromInt(CurrentWaveCount));
	FHDBEnemyWaveSpawnerTableRow* Row = EnemyWaveSpawnerDataTable->FindRow<FHDBEnemyWaveSpawnerTableRow>(RowName, FString());

	checkf(Row, TEXT("유효한 데이터 테이블이 없음"));

	return Row;
}
