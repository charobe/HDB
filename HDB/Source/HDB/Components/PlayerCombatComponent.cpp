// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerCombatComponent.h"
#include "Item/HDBPlayerWeapon.h"

AHDBPlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<AHDBPlayerWeapon>(GetCharacterOwnedWeaponByTag(InWeaponTag));
}
