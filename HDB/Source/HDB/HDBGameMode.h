// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HDBGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API AHDBGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Died(APlayerCharacter *DeadPlayer);

protected:
	virtual void BeginPlay() override;

private:
	class APlayerCharacter* PC;
};
