// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HDBGameModeBase.h"
#include "Player/HDBPlayerController.h"

AHDBGameModeBase::AHDBGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn>ThirdPersonClassRef(TEXT(" / Game / ThirdPerson / Blueprints / BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));

	if (ThirdPersonClassRef.Class)
	{
		DefaultPawnClass = ThirdPersonClassRef.Class;
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
