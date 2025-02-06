// Fill out your copyright notice in the Description page of Project Settings.


#include "HDBCharacterNonPlayer.h"

AHDBCharacterNonPlayer::AHDBCharacterNonPlayer()
{
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
