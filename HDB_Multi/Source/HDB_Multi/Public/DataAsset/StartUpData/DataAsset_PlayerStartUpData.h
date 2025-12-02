// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Type/HDBStructType.h"
#include "DataAsset/StartUpData/DataAsset_StartUpData.h"
#include "DataAsset_PlayerStartUpData.generated.h"



/**
 * 
 */
UCLASS()
class HDB_MULTI_API UDataAsset_PlayerStartUpData : public UDataAsset_StartUpData
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UHDBAbilitySystemComponent* ASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FHDBPlayerAbilitySet> PlayerStartUpAbilitySets;
	
};
