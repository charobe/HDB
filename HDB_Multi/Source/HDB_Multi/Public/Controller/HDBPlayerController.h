// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "HDBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HDB_MULTI_API AHDBPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:

	AHDBPlayerController();

	virtual FGenericTeamId GetGenericTeamId() const;

private:
	FGenericTeamId PlayerTeamID;
};
