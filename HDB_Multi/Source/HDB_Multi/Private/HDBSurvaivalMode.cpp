// Fill out your copyright notice in the Description page of Project Settings.


#include "HDBSurvaivalMode.h"
#include "GameState/HDBSurvivalState.h"
#include "Engine/AssetManager.h"
#include "Character/HDBEnemyCharacter.h"

#include "HDBDebugHelper.h"

AHDBSurvaivalMode::AHDBSurvaivalMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
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
	PreLoadNextWaveEnemies();

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
				PreLoadNextWaveEnemies();
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

void AHDBSurvaivalMode::PreLoadNextWaveEnemies()
{
	if (HasFinishedAllWaves())
	{
		return;
	}

	for (const FHDBEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;
		if (PreLoadedEnemyClassMap.Contains(SpawnerInfo.SoftEnemyClassToSpawn))
		{
			continue;
		}

		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[SpawnerInfo, this]()
				{
					if (UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
					{
						PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);

						Debug::Print(LoadedEnemyClass->GetName() + TEXT(" is loaded"));
					}
				}
			)
		);
	}
}

FHDBEnemyWaveSpawnerTableRow* AHDBSurvaivalMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName(*FString::Printf(TEXT("Wave%d"), CurrentWaveCount));

	FHDBEnemyWaveSpawnerTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow<FHDBEnemyWaveSpawnerTableRow>(RowName, FString());

	checkf(FoundRow, TEXT("Could not find a valid row under the name %s in the data table"), *RowName.ToString());

	return FoundRow;
}
