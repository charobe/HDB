// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/HDBGameplayAbility.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"

void UHDBGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec);

    if (AbilityActivationPolicy == EHDBAbilityActivationPolicy::OnGiven)
    {
        if (ActorInfo && !Spec.IsActive())
        {
            const bool bIsServer = ActorInfo->IsNetAuthority();
            const bool bIsLocallyControlled = ActorInfo->IsLocallyControlled();

            if (bIsServer || bIsLocallyControlled)
            {
                ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
            }
        }
    }
}

void UHDBGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility,
    bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    if (AbilityActivationPolicy == EHDBAbilityActivationPolicy::OnGiven)
    {
        if (ActorInfo && ActorInfo->IsNetAuthority())
        {
            // 가능하면 bRemoveAfterActivation 사용 권장
            ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
        }
    }
}