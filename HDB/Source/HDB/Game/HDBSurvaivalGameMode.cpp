#include "Game/HDBSurvaivalGameMode.h"
#include "Engine/AssetManager.h"
#include "Character/HDBEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "NavigationSystem.h"

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
			CurrentSpawnedEnemyCount += TrySpawnWaveEnemy();

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

int32 AHDBSurvaivalGameMode::TrySpawnWaveEnemy()
{
	if (TargetPointArray.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPointArray);
	}

	uint32 ElapsedTimefromEnemySpawn = 0;

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (const FHDBEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.EnemyClassToSpawn.IsNull()) continue;
		const int32 NumToSpawn = FMath::RandRange(SpawnerInfo.MinPerSpawnCount, SpawnerInfo.MaxPerSpawnCount);
		UClass* LoadedEnemyClass = PreLoadedEnemyClass.FindChecked(SpawnerInfo.EnemyClassToSpawn);
		
		for (int32 i = 0; i < NumToSpawn; i++)
		{
			const int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPointArray.Num() - 1);
			const FVector SpawnOrigin = TargetPointArray[RandomTargetPointIndex]->GetActorLocation();
			const FRotator SpawnRotation = TargetPointArray[RandomTargetPointIndex]->GetActorForwardVector().ToOrientationRotator();
		
			FVector RandomLocation;
			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnOrigin, RandomLocation, 400.f);
			
			RandomLocation += FVector(0.f, 0.f, 150.f);

			AHDBEnemyCharacter*	SpawnedEnemy = GetWorld()->SpawnActor<AHDBEnemyCharacter>(LoadedEnemyClass, RandomLocation, SpawnRotation, SpawnParam);
		
			if (SpawnedEnemy)
			{
				ElapsedTimefromEnemySpawn++;
				TotalSpawnedEnemyConut++;
			}

			if (!ShouldKeepSpawnEnemy())
			{
				return ElapsedTimefromEnemySpawn;
			}
		}
	}

	return ElapsedTimefromEnemySpawn;
}

bool AHDBSurvaivalGameMode::ShouldKeepSpawnEnemy() const
{
	return TotalSpawnedEnemyConut < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpawnThisWave;
}
