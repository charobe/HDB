// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HDBAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class HDB_MULTI_API UHDBAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "HDB|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);
};
