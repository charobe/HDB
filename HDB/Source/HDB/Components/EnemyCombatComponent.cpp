// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnemyCombatComponent.h"
#include "Character/HDBEnemyCharacter.h"
#include "Components/BoxComponent.h"

#include "HDBDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (HitActor)
	{
		Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" is hitting") + HitActor->GetActorNameOrLabel());
	}
}

void UEnemyCombatComponent::ToggleBodyCollsionBoxCollsion(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AHDBEnemyCharacter* OwningEnemyCharacter = GetOwningPawn<AHDBEnemyCharacter>();

	check(OwningEnemyCharacter);

	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollsionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollsionBox();

	check(LeftHandCollisionBox && RightHandCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}

	if (bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}
