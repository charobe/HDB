// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/DataAsset_StartUpDataBase.h"
#include "GameplayTagContainer.h"
#include "DataAsset_PlayerStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FHDBPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHDBGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

/**
 * 
 */
UCLASS()
class HDB_API UDataAsset_PlayerStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UPlayerAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta=(TitleProperty = "InputTag"))
	TArray<FHDBPlayerAbilitySet> PlayerStartUpAbilitySet;

};
