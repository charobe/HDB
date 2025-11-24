// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpData.generated.h"

class UHDBGameplayAbility;
class UHDBAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class HDB_MULTI_API UDataAsset_StartUpData : public UDataAsset
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "HDB|Startup")
    void GiveToAbilitySystemComponent(UHDBAbilitySystemComponent* ASCToGive, int32 ApplyLevel = 1) const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "DisplayName"))
    TArray<TSubclassOf<UHDBGameplayAbility>> ActivateOnGivenAbility;

    UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "DisplayName"))
    TArray<TSubclassOf<UHDBGameplayAbility>> ReactiveAbility;

    void GrantAbility(const TArray<TSubclassOf<UHDBGameplayAbility>>& AbilitiesToGive,
        UHDBAbilitySystemComponent* ASCToGive, int32 ApplyLevel = 1) const;
};