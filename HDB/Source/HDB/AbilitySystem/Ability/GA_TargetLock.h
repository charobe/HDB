// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/HDBPlayerGameplayAbility.h"
#include "GA_TargetLock.generated.h"

class UHDBWidgetBase;
/**
 * 
 */

UCLASS()
class HDB_API UGA_TargetLock : public UHDBPlayerGameplayAbility
{
	GENERATED_BODY()

protected:
	// UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//

	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

	
private:
	void LockOnTarget();
	void GetActorsToLock();

	AActor* GetNearestTarget(const TArray<AActor*>& InActors);
	void DrawTargetLockWidget();
	void SetTargetLockWidgetPosition();

	void CancelTargetLock();
	void CleanArray();

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TraceDistance = 5000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	FVector TraceBoxSize = FVector(5000.f, 5000.f, 300.f);

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	bool bShowDebugShape = false;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TSubclassOf<UHDBWidgetBase> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float RotationInterpSpeed = 10.f;

	UPROPERTY()
	TArray<AActor*> ActorsToLock;

	UPROPERTY()
	AActor* CurrentLockedActor;

	UPROPERTY()
	UHDBWidgetBase* TargetLockWidget;

	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;
};
