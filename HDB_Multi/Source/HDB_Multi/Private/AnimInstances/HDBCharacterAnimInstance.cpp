// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/HDBCharacterAnimInstance.h"
#include "Character/HDBCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

void UHDBCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<AHDBCharacterBase>(TryGetPawnOwner());

	if (GetWorld() && GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	OwningCharacter = Cast<AHDBCharacterBase>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}

}

void UHDBCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (GetWorld() && GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	if (!OwningCharacter)
	{
		OwningCharacter = Cast<AHDBCharacterBase>(TryGetPawnOwner());
		if (OwningCharacter)
		{
			OwningMovementComponent = OwningCharacter->GetCharacterMovement();
		}
	}
	else if (!OwningMovementComponent)
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
