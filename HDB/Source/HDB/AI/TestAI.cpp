// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TestAI.h"

void ATestAI::BeginPlay()
{
    Super::BeginPlay();

    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
    }
}