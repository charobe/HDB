// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HDBGameplayTag.h"
#include "HDBFunctionLibrary.h"

#include "HDBDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	APawn* OwnerPawn = GetOwningPawn<APawn>();
	if (!OwnerPawn || !OwnerPawn->HasAuthority()) return;
	if (OverlappedActor.Contains(HitActor))
	{
		return;
	}

	OverlappedActor.AddUnique(HitActor);

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UHDBFunctionLibrary::NativeDoesActorHaveTag(HitActor, HDBGameplayTags::Player_Status_Blocking);	
	const bool bIsMyAttackUnblockable = false;
	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
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
			HDBGameplayTags::Shared_Event_MeleeAttack,
			EventData
		);
	}
}
