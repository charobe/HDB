// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/HDBAIController.h"
#include "Navigation/CrowdFollowingComponent.h"

#include "HDBDebugHelper.h"

AHDBAIController::AHDBAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::Print(TEXT("CrowdFollowingComponent valid"), FColor::Green);
	}
}
