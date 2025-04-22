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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<class UEnemyCombatComponent> EnemyCombatComponent;

public:
	FORCEINLINE TObjectPtr<class UEnemyCombatComponent> GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
