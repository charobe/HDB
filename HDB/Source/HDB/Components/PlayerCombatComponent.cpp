// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerCombatComponent.h"
#include "Item/HDBPlayerWeapon.h"

#include "HDBDebugHelper.h"

AHDBPlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<AHDBPlayerWeapon>(GetCharacterOwnedWeaponByTag(InWeaponTag));
}

void UPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("공격") + HitActor->GetActorNameOrLabel(), FColor::Green);
}

void UPlayerCombatComponent::OnWeaponPulledTargetActor(AActor* InteractedActor)
{
    Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("공격한 무기") + InteractedActor->GetActorNameOrLabel(), FColor::Red);
}
