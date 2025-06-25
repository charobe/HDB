// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/HDBDropItemBase.h"
#include "HDBPotionBase.generated.h"

class UPlayerAbilitySystemComponent;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class HDB_API AHDBPotionBase : public AHDBDropItemBase
{
	GENERATED_BODY()
	
public:
	void Use(UPlayerAbilitySystemComponent* Component, int32 ApplyLevel);

protected:
	virtual void OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Potion Used"))
	void BP_PotionUsed();


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
};
