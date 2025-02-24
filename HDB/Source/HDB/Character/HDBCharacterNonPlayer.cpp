// Fill out your copyright notice in the Description page of Project Settings.


#include "HDBCharacterNonPlayer.h"
#include "AI/HDBAIController.h"

AHDBCharacterNonPlayer::AHDBCharacterNonPlayer()
{
	AIControllerClass = AHDBAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AHDBCharacterNonPlayer::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}
