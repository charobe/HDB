// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PawnCombatComponent.h"
#include "Character/HDBCharacterBase.h"
#include "Components/BoxComponent.h"

#include "HDBDebugHelper.h"

void UPawnCombatComponent::ToggleCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AHDBCharacterBase* OwningCharacter = GetOwningPawn<AHDBCharacterBase>();

	check(OwningCharacter);

	if (!OwningCharacter->HasAuthority())
	{
		return;
	}

	UBoxComponent* LeftHandCollisionBox = OwningCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningCharacter->GetRightHandCollisionBox();

	check(LeftHandCollisionBox && RightHandCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		if (bShouldEnable)
		{
			OverlappedActor.Reset();		
			LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		break;

	case EToggleDamageType::RightHand:
		if (bShouldEnable)
		{
			OverlappedActor.Reset();
			RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		break;

	default:
		break;
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPawnCombatComponent::OnPulledFromTargetActor(AActor* InteractedActor)
{
}
