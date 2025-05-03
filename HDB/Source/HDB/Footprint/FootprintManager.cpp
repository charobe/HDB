// Fill out your copyright notice in the Description page of Project Settings.


#include "FootprintManager.h"

UFootprintManager* UFootprintManager::Instance = nullptr;

UFootprintManager* UFootprintManager::Get(UWorld* World)
{
    if (!Instance)
    {
        Instance = NewObject<UFootprintManager>();
        Instance->AddToRoot();
    }
    return Instance;
}

void UFootprintManager::AddFootprint(const FVector& Location, float CurrentTime)
{
    FootprintInfos.Add(FFootprintInfo(Location, CurrentTime));
    //UE_LOG(LogTemp, Log, TEXT("Footprint added at %s (Time=%.2f)"), *Location.ToString(), CurrentTime);
}

void UFootprintManager::Update(float CurrentTime, float MaxLifetimeSeconds)
{
    FootprintInfos.RemoveAll([&](const FFootprintInfo& Info)
        {
            return (CurrentTime - Info.SpawnTime) > MaxLifetimeSeconds;
        });
}

TArray<FVector> UFootprintManager::GetActiveFootprintLocations(float CurrentTime, float MaxLifetimeSeconds) const
{
    TArray<FVector> Result;
    for (const FFootprintInfo& Info : FootprintInfos)
    {
        if ((CurrentTime - Info.SpawnTime) <= MaxLifetimeSeconds)
        {
            Result.Add(Info.Location);
        }
    }
    return Result;
}