#include "Game/HDBSurvaivalGameMode.h"

void AHDBSurvaivalGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AHDBSurvaivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHDBSurvaivalGameMode::SetCurrentSurvivalGameModeState(EHDBSurvivalGameModeState State)
{
	CurrentSurvivalGameModeState = State;

	OnSurvivalGameModeStateChanged.Broadcast(CurrentSurvivalGameModeState);
}
