// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUpData/DataAsset_StartUpData.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"
#include "AbilitySystem/Ability/HDBGameplayAbility.h"

#include "DataAsset/StartUpData/DataAsset_StartUpData.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"
#include "AbilitySystem/Ability/HDBGameplayAbility.h"
#include "AbilitySystemComponent.h"

static bool HasAbilityClass(UAbilitySystemComponent* ASC, TSubclassOf<UGameplayAbility> AbilityClass)
{
    if (!ASC || !AbilityClass) return false;
    return ASC->FindAbilitySpecFromClass(AbilityClass) != nullptr;
}

void UDataAsset_StartUpData::GiveToAbilitySystemComponent(UHDBAbilitySystemComponent* ASCToGive, int32 ApplyLevel) const
{
    check(ASCToGive);

    const AActor* Owner = ASCToGive->GetOwnerActor();
    if (!Owner || !Owner->HasAuthority())   
    {
        return;
    }
    if (!ASCToGive->GetAvatarActor())       
    {
        return;
    }

    for (const TSubclassOf<UHDBGameplayAbility>& Ability : ActivateOnGivenAbility)
    {
        if (!Ability) continue;
        if (HasAbilityClass(ASCToGive, Ability)) continue;

        
        FGameplayAbilitySpec Spec(Ability, ApplyLevel, INDEX_NONE, ASCToGive->GetAvatarActor());
        Spec.RemoveAfterActivation = true;
        ASCToGive->GiveAbility(Spec);
        ASCToGive->TryActivateAbility(Spec.Handle);
    }

    GrantAbility(ReactiveAbility, ASCToGive, ApplyLevel);
}

void UDataAsset_StartUpData::GrantAbility(const TArray<TSubclassOf<UHDBGameplayAbility>>& AbilitiesToGive,
    UHDBAbilitySystemComponent* ASCToGive, int32 ApplyLevel) const
{
    if (AbilitiesToGive.IsEmpty()) return;

    for (const TSubclassOf<UHDBGameplayAbility>& Ability : AbilitiesToGive)
    {
        if (!Ability) continue;
        if (HasAbilityClass(ASCToGive, Ability)) continue;

        FGameplayAbilitySpec Spec(Ability, ApplyLevel, INDEX_NONE, ASCToGive->GetAvatarActor());
        ASCToGive->GiveAbility(Spec);
    }
}