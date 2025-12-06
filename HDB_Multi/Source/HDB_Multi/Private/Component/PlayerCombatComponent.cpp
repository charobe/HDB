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
}

void UPlayerCombatComponent::OnPulledFromTargetActor(AActor* InteractedActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("'s weapon pulled from ") + InteractedActor->GetActorNameOrLabel(), FColor::Red);
}
