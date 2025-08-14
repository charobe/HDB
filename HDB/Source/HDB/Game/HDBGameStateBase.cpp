// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HDBGameStateBase.h"

void AHDBGameStateBase::HandleBeginPlay()
{
	Super::HandleBeginPlay();
}

void AHDBGameStateBase::OnRep_ReplicatedHasBegunPlay()
{
	Super::OnRep_ReplicatedHasBegunPlay();
}
