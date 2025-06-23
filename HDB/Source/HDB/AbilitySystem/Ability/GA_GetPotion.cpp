// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_GetPotion.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/HDBCharacterPlayer.h"
#include "Item/HDBPotionBase.h"


void UGA_GetPotion::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_GetPotion::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_GetPotion::GetPotion()
{
	TracedPotions.Empty();

	TArray<FHitResult> TraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() + GetPlayerCharacterFromActorInfo()->GetActorUpVector() * -1 * TraceDistance,
		TraceBoxSize / 2.0f,
		(GetPlayerCharacterFromActorInfo()->GetActorUpVector() * -1).ToOrientationRotator(),
		TraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for (const FHitResult& TraceHit : TraceHits)
	{
		if (AHDBPotionBase* DetectedActor = Cast<AHDBPotionBase>(TraceHit.GetActor()))
		{
			TracedPotions.AddUnique(DetectedActor);
		}
	}

	if (TracedPotions.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}
