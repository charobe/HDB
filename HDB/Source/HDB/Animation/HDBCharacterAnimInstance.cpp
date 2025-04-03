// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HDBCharacterAnimInstance.h"
#include "Character/HDBCharacterPlayer.h"


void UHDBCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningCharacter = Cast<AHDBCharacterPlayer>(OwningCharacter);
	}
}

void UHDBCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
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
		bEnterRelaxState = (IdleElpasedTime >= bEnterRelaxStateThreshold);
	}
}
