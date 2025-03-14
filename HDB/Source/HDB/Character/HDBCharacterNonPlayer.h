// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HDBCharacterBase.h"
#include "Interface/HDBSpiderAIInterface.h"
#include "HDBCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API AHDBCharacterNonPlayer : public AHDBCharacterBase, public IHDBSpiderAIInterface
{
	GENERATED_BODY()

public:
	AHDBCharacterNonPlayer();

protected:
	void SetDead() override;

// AI Section
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange()  override;
	virtual float GetAttackRange()  override; 
	virtual float GetAITurnSpeed()  override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinshed& InOnAttackFinished) override;
	virtual void AttackByAI() override;
};
