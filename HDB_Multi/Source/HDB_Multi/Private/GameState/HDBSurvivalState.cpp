// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/HDBSurvivalState.h"
#include "Net/UnrealNetwork.h"


AHDBSurvivalState::AHDBSurvivalState()
{
	bReplicates = true;

}

void AHDBSurvivalState::ServerSetState(EHDBSurvialGameModeState NewState)
{
	if (!HasAuthority()) return;

	if (CurrentState == NewState) return;

	CurrentState = NewState;

	OnSurvivalStateChanged.Broadcast(CurrentState);
}

void AHDBSurvivalState::ServerSetWaveInfo(int32 NewCurrentWaveIndex, int32 NewTotalWaves)
{
	if (!HasAuthority()) return;

	CurrentWaveCount = NewCurrentWaveIndex;
	TotalWaves = NewTotalWaves;

	OnSurvivalWaveChanged.Broadcast(CurrentWaveCount, TotalWaves);
}

void AHDBSurvivalState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHDBSurvivalState, CurrentState);
	DOREPLIFETIME(AHDBSurvivalState, CurrentWaveCount);
	DOREPLIFETIME(AHDBSurvivalState, TotalWaves);
}

void AHDBSurvivalState::OnRep_CurrentState()
{
	OnSurvivalStateChanged.Broadcast(CurrentState);

}

void AHDBSurvivalState::OnRep_WaveInfo()
{
	OnSurvivalWaveChanged.Broadcast(CurrentWaveCount, TotalWaves);
}
