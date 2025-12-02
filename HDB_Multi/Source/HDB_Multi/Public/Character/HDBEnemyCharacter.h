// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HDBCharacterBase.h"
#include "HDBEnemyCharacter.generated.h"

class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class HDB_MULTI_API AHDBEnemyCharacter : public AHDBCharacterBase
{
	GENERATED_BODY()
	
public:
	AHDBEnemyCharacter();

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Combat")
	TObjectPtr<UEnemyCombatComponent> EnemyCombatComponent;

public:
	FORCEINLINE TObjectPtr<UEnemyCombatComponent> GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
