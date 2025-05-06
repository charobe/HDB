// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HDBPlayerController.h"

AHDBPlayerController::AHDBPlayerController()
{
	PlayerTeamID = FGenericTeamId(0);
}

FGenericTeamId AHDBPlayerController::GetGenericTeamId() const
{
	return PlayerTeamID;
}
