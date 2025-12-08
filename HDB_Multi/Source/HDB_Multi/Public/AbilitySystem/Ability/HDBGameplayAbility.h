// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HDBFunctionLibrary.h"
#include "Type/HDBEnumType.h"
#include "HDBGameplayAbility.generated.h"


class UPawnCombatComponent;
class UHDBAbilitySystemComponent;

UENUM(BlueprintType)
enum class EHDBAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};
/**
 * 
 */
UCLASS()
class HDB_MULTI_API UHDBGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "HDBAbility")
	EHDBAbilityActivationPolicy AbilityActivationPolicy = EHDBAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	UPawnCombatComponent* GetPawnCombatComponent() const;

	UFUNCTION(BlueprintPure, Category = "HDB|Ability")
	UHDBAbilitySystemComponent* GetHDBAbilitySystemComponentFromActor() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "HDB|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EHDBSuccessType& OutSuccessType);
};
