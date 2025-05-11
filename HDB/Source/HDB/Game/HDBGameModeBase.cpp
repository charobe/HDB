// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HDBGameModeBase.h"
#include "Player/HDBPlayerController.h"

AHDBGameModeBase::AHDBGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/HDB/Character/Player/BP_HDBCharacterPlayer.BP_HDBCharacterPlayer_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	// DefaultPawnClass
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/HDB.HDBPlayerController"));

	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
	PlayerControllerClass = AHDBPlayerController::StaticClass();

}

void AHDBGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}
