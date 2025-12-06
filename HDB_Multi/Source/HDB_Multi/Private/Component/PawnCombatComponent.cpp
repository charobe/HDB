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
			LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			}
		else
		{
			LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		//LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;

	case EToggleDamageType::RightHand:
		if (bShouldEnable)
		{
			RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		//RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;

	default:
		break;
	}

	//if (!bShouldEnable)
	//{
//		OverlappedActors.Empty();
//	}

}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPawnCombatComponent::OnPulledFromTargetActor(AActor* InteractedActor)
{
}
