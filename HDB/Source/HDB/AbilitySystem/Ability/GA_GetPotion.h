// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/HDBPlayerGameplayAbility.h"
#include "GA_GetPotion.generated.h"

class AHDBPotionBase;

/**
 * 
 */
UCLASS()
class HDB_API UGA_GetPotion : public UHDBPlayerGameplayAbility
{
	GENERATED_BODY()
	
protected:
	// UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//

	UFUNCTION(BlueprintCallable)
	void GetPotion();

private:
	UPROPERTY(EditDefaultsOnly)
	float TraceDistance = 50.0f;

	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(100.f);
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceChannel;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebugShape = false;

	UPROPERTY()
	TArray<AHDBPotionBase*> TracedPotions;
};
