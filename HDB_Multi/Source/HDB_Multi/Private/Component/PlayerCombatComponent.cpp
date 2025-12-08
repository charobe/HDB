// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PlayerCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HDBGameplayTag.h"

#include "HDBDebugHelper.h"

void UPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	APawn* OwnerPawn = GetOwningPawn();
	if (!OwnerPawn || !OwnerPawn->HasAuthority())
	{
		return;
	}

	if (OverlappedActor.Contains(HitActor))
	{
		return;
	}

	OverlappedActor.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		HDBGameplayTags::Shared_Event_MeleeAttack,
		Data);


	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		HDBGameplayTags::Player_Event_HitPause,
		FGameplayEventData());
}

void UPlayerCombatComponent::OnPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		HDBGameplayTags::Player_Event_HitPause,
		FGameplayEventData());
}
