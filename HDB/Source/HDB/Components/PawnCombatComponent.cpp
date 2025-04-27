// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PawnCombatComponent.h"
#include "Item/HDBWeaponBase.h"
#include "Components/BoxComponent.h"

#include "HDB/HDBDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToResiter, AHDBWeaponBase* InWeaponToResiter, bool bResgiterAsEquippedWeapon)
{
	checkf(!CharacterOwnedWeaponMap.Contains(InWeaponTagToResiter), TEXT("무기 %s 가 이미 등록되었습니다."), *InWeaponTagToResiter.ToString());
	check(InWeaponToResiter);
	
	CharacterOwnedWeaponMap.Emplace(InWeaponTagToResiter, InWeaponToResiter);

	if (bResgiterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToResiter;
	}
}

AHDBWeaponBase* UPawnCombatComponent::GetCharacterOwnedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterOwnedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AHDBWeaponBase* const* FoundWeapon = CharacterOwnedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}

	return nullptr;
}

AHDBWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return  nullptr;
	}
	return GetCharacterOwnedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollsion(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AHDBWeaponBase*  WeaponToToggle = GetCharacterCurrentEquippedWeapon();
	
		check(WeaponToToggle);

		if (bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	
	//

}
