// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HDBGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API AHDBGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
	virtual void HandleBeginPlay() override;
	
	virtual void OnRep_ReplicatedHasBegunPlay() override;
};
