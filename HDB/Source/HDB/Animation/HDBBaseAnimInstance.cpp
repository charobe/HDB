// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HDBBaseAnimInstance.h"
#include "Character/HDBCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"


void UHDBBaseAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AHDBCharacterPlayer>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UHDBBaseAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
