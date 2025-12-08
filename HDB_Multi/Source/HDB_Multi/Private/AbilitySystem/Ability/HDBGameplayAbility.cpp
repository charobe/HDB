// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/HDBGameplayAbility.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"
#include "Component/PawnCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

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
            ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
        }
    }
}

UPawnCombatComponent* UHDBGameplayAbility::GetPawnCombatComponent() const
{

    return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UHDBAbilitySystemComponent* UHDBGameplayAbility::GetHDBAbilitySystemComponentFromActor() const
{
    return Cast<UHDBAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UHDBGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
    UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

    check(TargetASC && InSpecHandle.IsValid());

    return GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
        *InSpecHandle.Data,
        TargetASC
    );
}

FActiveGameplayEffectHandle UHDBGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EHDBSuccessType& OutSuccessType)
{
    FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

    OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EHDBSuccessType::Success : EHDBSuccessType::Failed;

    return ActiveGameplayEffectHandle;
}
