// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnComponentBase.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate, float, NewPercent);

class UHDBAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class HDB_MULTI_API UPawnUIComponent : public UPawnComponentBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentHealthChanged;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	float GetCurrentHealthRatio() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	UHDBAbilitySystemComponent* GetHDBASC() const;

};
