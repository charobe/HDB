// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HDBWidgetBase.generated.h"

class UPlayerUIComponent;
/**
 * 
 */
UCLASS()
class HDB_API UHDBWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisPlayName = "OnOwningPlayerUIComponentInitalized"))
	void BP_OnOwningPlayerUIComponentInitalized(UPlayerUIComponent* OwningPlayerUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisPlayName = "OnOwningEnemyUIComponentInitalized"))
	void BP_OnOwningEnemyUIComponentInitalized(UEnemyUIComponent* OwningEnemyUIComponent);
public:

	UFUNCTION(BlueprintCallable)
	void InitEnemyCratedWidget(AActor* OwningEnemyActor);


};
