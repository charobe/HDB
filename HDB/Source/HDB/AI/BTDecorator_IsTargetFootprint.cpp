// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsTargetFootprint.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsTargetFootprint::UBTDecorator_IsTargetFootprint()
{
    NodeName = "Is Target Footprint";
}

bool UBTDecorator_IsTargetFootprint::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp) {
        return false;

    }

    FVector TargetLocation = BlackboardComp->GetValueAsVector(TargetLocationKey.SelectedKeyName);

    if (!TargetLocation.IsNearlyZero()) {
        return true;

    }

    return false; 
}
