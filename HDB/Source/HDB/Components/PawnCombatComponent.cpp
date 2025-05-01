// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PawnCombatComponent.h"
#include "Item/HDBWeaponBase.h"
#include "Components/BoxComponent.h"

#include "HDB/HDBDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AHDBWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	if (CharacterOwnedWeaponMap.Contains(InWeaponTagToRegister))
	{
		return;
	}

	check(InWeaponToRegister);
	
	CharacterOwnedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledTargetActor);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
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
			OverlappedActors.Empty();
		}
	}
	
	//

}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPawnCombatComponent::OnWeaponPulledTargetActor(AActor* InteractedActor)
{
}

AHDBWeaponBase* UPawnCombatComponent::GetRegisteredWeaponByTag(FGameplayTag WeaponTag) const
{
	if (AHDBWeaponBase* const* FoundWeaponPtr = CharacterOwnedWeaponMap.Find(WeaponTag))
	{
		return *FoundWeaponPtr;
	}
	return nullptr;
}

void UPawnCombatComponent::UnregisterWeapon(FGameplayTag WeaponTagToRemove)
{
	AHDBWeaponBase* const* FoundWeaponPtr = CharacterOwnedWeaponMap.Find(WeaponTagToRemove);
	if (!FoundWeaponPtr || !IsValid(*FoundWeaponPtr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UnregisterWeapon: 등록된 무기를 찾을 수 없습니다. (%s)"), *WeaponTagToRemove.ToString());
		return;
	}

	AHDBWeaponBase* WeaponToRemove = *FoundWeaponPtr;

	// 1. 소켓에서 분리
	WeaponToRemove->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	// 2. 이벤트 바인딩 해제 (안정성 보강용)
	WeaponToRemove->OnWeaponHitTarget.Unbind();
	WeaponToRemove->OnWeaponPulledFromTarget.Unbind();

	// 3. 액터 제거
	WeaponToRemove->Destroy();

	// 4. Map에서 제거
	CharacterOwnedWeaponMap.Remove(WeaponTagToRemove);

}