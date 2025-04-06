// Fill out your copyright notice in the Description page of Project Settings.


#include "HDBPlayerAnimInstance.h"
#include "Character/HDBCharacterPlayer.h"

void UHDBPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningCharacter = Cast<AHDBCharacterPlayer>(OwningCharacter);
	}
}

void UHDBPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElpasedTime = 0.f;
		bEnterRelaxState = false;
	}
	else
	{
		IdleElpasedTime += DeltaSeconds;
		bEnterRelaxState = (IdleElpasedTime >= EnterRelaxStateThreshold);
	}
}
