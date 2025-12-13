// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PawnUIComponent.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"
#include "Character/HDBCharacterBase.h"
#include "AbilitySystem/HDBAttributeSet.h"

float UPawnUIComponent::GetCurrentHealthRatio() const
{
    if (UHDBAbilitySystemComponent* ASC = GetHDBASC())
    {
        const float Cur =
            ASC->GetNumericAttribute(UHDBAttributeSet::GetCurrentHealthAttribute());
        const float Max =
            ASC->GetNumericAttribute(UHDBAttributeSet::GetMaxHealthAttribute());

        return FMath::IsNearlyZero(Max) ? 0.f : Cur / Max;
    }
    return 0.f;
}

UHDBAbilitySystemComponent* UPawnUIComponent::GetHDBASC() const
{

    if (const AHDBCharacterBase* Char = Cast<AHDBCharacterBase>(GetOwner()))
    {
        return Cast<UHDBAbilitySystemComponent>(Char->GetAbilitySystemComponent());
    }
    return nullptr;
}

