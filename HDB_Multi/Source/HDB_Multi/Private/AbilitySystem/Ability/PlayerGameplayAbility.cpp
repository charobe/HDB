// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/PlayerGameplayAbility.h"
#include "Character/HDBPlayerCharacter.h"
#include "Controller/HDBPlayerController.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"
#include "HDBGameplayTag.h"

AHDBPlayerCharacter* UPlayerGameplayAbility::GetPlayerCharacterFromActor()
{
	if (!CachedPlayerCharacter.IsValid())
	{
	
	CachedPlayerCharacter = Cast<AHDBPlayerCharacter>(CurrentActorInfo->AvatarActor);
}
	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

AHDBPlayerController* UPlayerGameplayAbility::GetPlayerControllerFromActor()
{
	if (!CachedPlayerController.IsValid())
	{

		CachedPlayerController = Cast<AHDBPlayerController>(CurrentActorInfo->AvatarActor);
	}
	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UPlayerCombatComponent* UPlayerGameplayAbility::GetPlayerCombatComponentFromActor()
{
	return GetPlayerCharacterFromActor()->GetPlayerCombatComponent();
}

FGameplayEffectSpecHandle UPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCurrentComboCount)
{
	if (!ensure(EffectClass))
	{
		return FGameplayEffectSpecHandle();
	}

	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC)
	{
		return FGameplayEffectSpecHandle();
	}

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		HDBGameplayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage
	);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InCurrentComboCount);
	}

	return EffectSpecHandle;
}
