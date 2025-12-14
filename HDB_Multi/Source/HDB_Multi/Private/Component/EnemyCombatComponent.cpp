// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HDBGameplayTag.h"

#include "HDBDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActor.Contains(HitActor))
	{
		return;
	}

	OverlappedActor.AddUnique(HitActor);

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = false;
	const bool bIsMyAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			HDBGameplayTags::Shared_Event_MeleeAttack,
			EventData
		);
	}
}
