// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_TargetLock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/HDBCharacterPlayer.h"
#include "Kismet/GameplayStatics.h"

#include "HDBDebugHelper.h"

void UGA_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	LockOnTarget();

	Super::ActivateAbility(Handle,ActorInfo,ActivationInfo,TriggerEventData);
}

void UGA_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	CleanArray(); 

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_TargetLock::LockOnTarget()
{
	GetActorsToLock();
	if (ActorsToLock.IsEmpty())
	{
		CancelTargetLock();
		return;
	}
	CurrentLockedActor = GetNearestTarget(ActorsToLock);

	if (CurrentLockedActor)
	{
		Debug::Print(CurrentLockedActor->GetActorNameOrLabel());
	}
	else
	{
		CancelTargetLock();
	}
}

void UGA_TargetLock::GetActorsToLock()
{
	TArray<FHitResult> BoxTraceHit;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() + GetPlayerCharacterFromActorInfo()->GetActorForwardVector() * TraceDistance,
		TraceBoxSize / 2.f,
		GetPlayerCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHit,
		true
	);

	for (const FHitResult& TraceHit : BoxTraceHit)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != GetPlayerCharacterFromActorInfo())
			{
				ActorsToLock.AddUnique(HitActor);
			}
		}
	}
}

AActor* UGA_TargetLock::GetNearestTarget(const TArray<AActor*>& InActors)
{
	float Distance = 0.f;
	AActor* NearestActor = UGameplayStatics::FindNearestActor(GetPlayerCharacterFromActorInfo()->GetActorLocation(), InActors, Distance);	
	return NearestActor;
}

void UGA_TargetLock::CancelTargetLock()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UGA_TargetLock::CleanArray()
{
	ActorsToLock.Empty();
	CurrentLockedActor = nullptr;
	
}
