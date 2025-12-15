// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class UHDBWidgetBase;
/**
 * 
 */
UCLASS()
class HDB_MULTI_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UHDBWidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();

private:
	TArray<UHDBWidgetBase*> EnemyDrawnWidgets;
	
};
