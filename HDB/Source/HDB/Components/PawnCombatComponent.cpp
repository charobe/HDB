// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PawnCombatComponent.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToResiter, TArray<AHDBWeaponBase*> InWeaponToResiter, bool bResgiterAsEquippedWeapon)
{
	checkf(!CharacterOwnedWeaponMap.Contains(InWeaponTagToResiter), TEXT("무기 %s 가 이미 등록되었습니다."), *InWeaponTagToResiter.ToString());
	for (AHDBWeaponBase* InWeapon : InWeaponToResiter)
	{
		check(InWeapon);
	}

	CharacterOwnedWeaponMap.Emplace(InWeaponTagToResiter, InWeaponToResiter);

	if (bResgiterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToResiter;
	}
}

TArray<AHDBWeaponBase*> UPawnCombatComponent::GetCharacterOwnedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterOwnedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (const TArray<AHDBWeaponBase*>* FoundWeapon = CharacterOwnedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}

	return TArray<AHDBWeaponBase*>();
}

TArray<AHDBWeaponBase*> UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return TArray<AHDBWeaponBase*>();
	}
	return GetCharacterOwnedWeaponByTag(CurrentEquippedWeaponTag);
}
