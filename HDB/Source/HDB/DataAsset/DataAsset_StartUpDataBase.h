// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UHDBGameplayAbility;
class UPlayerAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class HDB_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UPlayerAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);


protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray < TSubclassOf<UHDBGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray < TSubclassOf<UHDBGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray < TSubclassOf<UHDBGameplayAbility>>& InAbilitiesToGive, UPlayerAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
}; 
