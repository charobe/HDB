// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HDBCharacterBase.h"
#include "HDBEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API AHDBEnemyCharacter : public AHDBCharacterBase
{
	GENERATED_BODY()
	
public:
	AHDBEnemyCharacter();

protected:

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<class UEnemyCombatComponent> EnemyCombatComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE TObjectPtr<class UEnemyCombatComponent> GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
