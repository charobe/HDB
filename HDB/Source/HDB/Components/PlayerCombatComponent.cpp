// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerCombatComponent.h"
#include "Item/HDBPlayerWeapon.h"
#include "Tag/HDBGameplayTag.h"
#include "AbilitySystemBlueprintLibrary.h"


#include "HDBDebugHelper.h"

AHDBPlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<AHDBPlayerWeapon>(GetCharacterOwnedWeaponByTag(InWeaponTag));
}

AHDBPlayerWeapon* UPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
    return Cast<AHDBPlayerWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UPlayerCombatComponent::GetPlayerCurrentEquippWeaponDamageAtLevel(float InLevel) const
{
    return GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if (OverlappedActors.Contains(HitActor))
    {
        return;
    }
    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        HDBGameplayTags::Shared_Event_MeleeHit,
        Data
    );
        
}

void UPlayerCombatComponent::OnWeaponPulledTargetActor(AActor* InteractedActor)
{
}
