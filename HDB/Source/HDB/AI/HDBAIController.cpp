// Fill out your copyright notice in the Description page of Project Settings.


#include "HDBAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"

#include"HDBDebugHelper.h"


void AHDBAIController::BeginPlay()
{
    Super::BeginPlay();

    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
    }

}

AHDBAIController::AHDBAIController(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
    if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
    {
        Debug::Print(TEXT("CrowdFollowingComponent valid"), FColor::Green);
    }

}

