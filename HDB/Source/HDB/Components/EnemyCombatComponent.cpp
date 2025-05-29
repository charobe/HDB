// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnemyCombatComponent.h"
#include "Character/HDBEnemyCharacter.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HDBFunctionLibrary.h"
#include "Tag/HDBGameplayTag.h"

#include "HDBDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	bool bIsValidBlock = false;

	const bool bIsTargetBlocking = UHDBFunctionLibrary::NativeDoesActorHaveTag(HitActor, HDBGameplayTags::Player_Status_Block);
	const bool bIsMyAttackUnblockable = UHDBFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), HDBGameplayTags::Enemy_Status_Unblockable);

	if (bIsTargetBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UHDBFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			HDBGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);

	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			HDBGameplayTags::Shared_Event_MeleeHit,
			EventData
		);

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

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}
