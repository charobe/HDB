// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HDBCharacterAnimInstance.h"
#include "Character/HDBCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"



void UHDBCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AHDBCharacterBase>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UHDBCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	float Direction = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	SmoothedDirection = FMath::FInterpTo(SmoothedDirection, Direction, DeltaSeconds, 6.0f);
	LocomotionDirection = FMath::RoundToFloat(SmoothedDirection / 45.0f) * 45.0f;
}
