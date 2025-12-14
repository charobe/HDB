// Fill out your copyright notice in the Description page of Project Settings.


#include "HDBSurvaivalMode.h"

void AHDBSurvaivalMode::BeginPlay()
{
	Super::BeginPlay();
}

void AHDBSurvaivalMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHDBSurvaivalMode::SetCurrentSurvialGameModeState(EHDBSurvialGameModeState InState)
{
	CurrentSurvialGameModeState = InState;

	OnSurvialGameModeStateChanged.Broadcast(CurrentSurvialGameModeState);
}
