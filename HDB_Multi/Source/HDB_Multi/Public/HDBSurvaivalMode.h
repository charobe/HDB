// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HDBGameModeBase.h"
#include "GameState/HDBSurvivalState.h" 
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "NavigationSystem.h"
#include "HDBSurvaivalMode.generated.h"

class AHDBEnemyCharacter;

USTRUCT(BlueprintType)
struct FHDBEnemyWaveSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AHDBEnemyCharacter> SoftEnemyClassToSpawn;

	UPROPERTY(EditAnywhere)
	int32 MinPerSpawnCount = 1;

	UPROPERTY(EditAnywhere)
	int32 MaxPerSpawnCount = 3;
};

USTRUCT(BlueprintType)
struct FHDBEnemyWaveSpawnerTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FHDBEnemyWaveSpawnerInfo> EnemyWaveSpawnerDefinitions;

	UPROPERTY(EditAnywhere)
	int32 TotalEnemyToSpawnThisWave = 1;
};

/**
 * 
 */
UCLASS()
class HDB_MULTI_API AHDBSurvaivalMode : public AHDBGameModeBase
{
	GENERATED_BODY()


public:
	AHDBSurvaivalMode();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetCurrentSurvialGameModeState(EHDBSurvialGameModeState InState);

	bool HasFinishedAllWaves() const;
	void PreLoadNextWaveEnemies();
	FHDBEnemyWaveSpawnerTableRow* GetCurrentWaveSpawnerTableRow() const;
	int32 TrySpawnWaveEnemies();
	bool ShouldKeepSpawnEnemies() const;


	UPROPERTY()
	EHDBSurvialGameModeState CurrentSurvialGameModeState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	UDataTable* EnemyWaveSpawnerDataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	int32 TotalWavesToSpawn;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	int32 CurrentWaveCount = 1;

	UPROPERTY()
	float TimePassedSinceStart = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float SpawnNewWaveWaitTime = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float SpawnEnemiesDelayTime = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float WaveCompletedWaitTime = 5.f;

	UPROPERTY()
	TMap< TSoftClassPtr < AHDBEnemyCharacter >, UClass* > PreLoadedEnemyClassMap;

	UPROPERTY()
	int32 CurrentSpawnedEnemiesCounter = 0;

	UPROPERTY()
	int32 TotalSpawnedEnemiesThisWaveCounter = 0;

	UPROPERTY()
	TArray<AActor*> TargetPointsArray;

};
