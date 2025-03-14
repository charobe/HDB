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

float AHDBCharacterNonPlayer::GetAIPatrolRadius()
{
	return 800.0f;
}

float AHDBCharacterNonPlayer::GetAIDetectRange()
{
	return 400.0f;
}

float AHDBCharacterNonPlayer::GetAttackRange()
{
	return 250.0f;
}

float AHDBCharacterNonPlayer::GetAITurnSpeed()
{
	return 0.0f;
}

void AHDBCharacterNonPlayer::SetAIAttackDelegate(const FAICharacterAttackFinshed& InOnAttackFinished)
{
}

void AHDBCharacterNonPlayer::AttackByAI()
{
}
