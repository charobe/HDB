// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/HDBCharacterAnimInstance.h"
#include "Character/HDBCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	bAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
