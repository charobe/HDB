// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HDBPlayerController.h"

void AHDBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
