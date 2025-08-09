#pragma once

#include "CoreMinimal.h"
#include "Game/HDBGameModeBase.h"
#include "HDBSurvaivalGameMode.generated.h"

class AHDBEnemyCharacter;

UENUM(BlueprintType)
enum class EHDBSurvivalGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesDone,
	PlayerDied
};

USTRUCT(BlueprintType)
struct FHDBEnemyWaveSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AHDBEnemyCharacter> EnemyClassToSpawn;

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


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivalGameModeStateChangedDelegate, EHDBSurvivalGameModeState, CurrentState);
/**
 * 
 */
UCLASS()
class HDB_API AHDBSurvaivalGameMode : public AHDBGameModeBase
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetCurrentSurvivalGameModeState(EHDBSurvivalGameModeState State);
	bool HasFinishedAllWave() const;
	void PreLoadNextWave();
	FHDBEnemyWaveSpawnerTableRow* GetCurrentWaveSpawnerTableRow() const;
	int32 TrySpawnWaveEnemy();
	bool ShouldKeepSpawnEnemy() const;

	UFUNCTION()
	void OnEnemyDestroyed(AActor* Actor);

	UPROPERTY()
	EHDBSurvivalGameModeState CurrentSurvivalGameModeState;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnSurvivalGameModeStateChangedDelegate OnSurvivalGameModeStateChanged;

	UPROPERTY()
	int32 CurrentSpawnedEnemyCount = 0;

	UPROPERTY()
	int32 TotalSpawnedEnemyConut = 0;

	UPROPERTY()
	TArray<AActor*> TargetPointArray;

	UPROPERTY()
	float elapsedTime = 0.f;


protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPriovateAccess = "true"))
	float SpawnWaitTime = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WaveDefinition", meta = (AllowPriovateAccess = "true"))
	float SpawnDelayTime = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPriovateAccess = "true"))
	float WaveCompletedWaitTime = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "WaveDefinition", meta = (AllowPriovateAccess = "true"))
	UDataTable* EnemyWaveSpawnerDataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category = "WaveDefinition", meta = (AllowPriovateAccess = "true"))
	int32 TotalWave;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPriovateAccess = "true"))
	int32 CurrentWaveCount = 1;

	UPROPERTY()
	TMap<TSoftClassPtr<AHDBEnemyCharacter>, UClass*> PreLoadedEnemyClass;
};
