// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HDBCharacterBase.h"
#include "HDBCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API AHDBCharacterNonPlayer : public AHDBCharacterBase
{
	GENERATED_BODY()

public:
	AHDBCharacterNonPlayer();

protected:
	void SetDead() override;

	
};
