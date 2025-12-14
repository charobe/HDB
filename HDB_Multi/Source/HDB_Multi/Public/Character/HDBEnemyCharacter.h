// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HDBCharacterBase.h"
#include "HDBEnemyCharacter.generated.h"

class UEnemyCombatComponent;
class UEnemyUIComponent;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class HDB_MULTI_API AHDBEnemyCharacter : public AHDBCharacterBase
{
	GENERATED_BODY()
	
public:
	AHDBEnemyCharacter();

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Combat")
	TObjectPtr<UEnemyCombatComponent> EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyWidgetComponent;

	virtual void PossessedBy(AController* NewController) override;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE TObjectPtr<UEnemyCombatComponent> GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
