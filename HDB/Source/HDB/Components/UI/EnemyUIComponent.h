// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PlayerUIComponent.h"
#include "EnemyUIComponent.generated.h"

class UHDBWidgetBase;
/**
 * 
 */
UCLASS()
class HDB_API UEnemyUIComponent : public UPlayerUIComponent
{
	GENERATED_BODY()
	
public: 
	UFUNCTION(BlueprintCallable)
	void RegisterWidget(UHDBWidgetBase* InWidget);
	
	UFUNCTION(BlueprintCallable)
	void RemoveWidget();

private:
	TArray<UHDBWidgetBase*> DrawnWidgets;
};
