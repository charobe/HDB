//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "GA/HDBGA_Attack.h"
//
//UHDBGA_Attack::UHDBGA_Attack()
//{
//	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
//}
//
//void UHDBGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
//{
//	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
//
//	AHDBCharacterBase* HDBCharacter = CastChecked<AHDBCharacterBase>(ActorInfo->AvatarActor.Get());
//	HDBCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
//
//	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), HDBCharacter->GetComboActionMontage());
//	PlayAttackTask->OnCompleted.AddDynamic(this, &UHDBGA_Attack::OnCompleteCallback);
//	PlayAttackTask->OnInterrupted.AddDynamic(this, &UHDBGA_Attack::OnInterruptedCallback);
//	PlayAttackTask->ReadyForActivation();
//}
//
//void UHDBGA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
//{
//}
//
//void UHDBGA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
//{
//}
//
//void UHDBGA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
//{
//}
//
//void UHDBGA_Attack::OnCompleteCallback()
//{
//}
//
//void UHDBGA_Attack::OnInterruptedCallback()
//{
//}
