// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FootprintManager.generated.h"

/**
 * 
 */

USTRUCT()
struct FFootprintInfo {
    GENERATED_BODY()

    FVector Location;
    float SpawnTime;

    FFootprintInfo() {}
    FFootprintInfo(const FVector& InLocation, float InSpawnTime)
        : Location(InLocation), SpawnTime(InSpawnTime) {}
};


UCLASS()
class HDB_MULTI_API UFootprintManager : public UObject
{
	GENERATED_BODY()

public:
    static UFootprintManager* Get(UWorld* World);

    void AddFootprint(const FVector& Location, float CurrentTime);

    void Update(float CurrentTime, float MaxLifetimeSeconds);

    TArray<FVector> GetActiveFootprintLocations(float CurrentTime, float MaxLifetimeSeconds) const;

private:
    static UFootprintManager* Instance;

    TArray<FFootprintInfo> FootprintInfos;
	
};
