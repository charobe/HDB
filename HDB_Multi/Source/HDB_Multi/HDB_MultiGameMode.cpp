// Copyright Epic Games, Inc. All Rights Reserved.

#include "HDB_MultiGameMode.h"
#include "HDB_MultiCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHDB_MultiGameMode::AHDB_MultiGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
