// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/PawnCombatInterface.h"
#include "Interface/PawnUIInterface.h"
#include "HDBCharacterBase.generated.h"

class UHDBAbilitySystemComponent;
class UHDBAttributeSet;
class UBoxComponent;
class UDataAsset_StartUpData;
class UMotionWarpingComponent;

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*);

UCLASS()
class HDB_MULTI_API AHDBCharacterBase : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHDBCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;


	FOnTargetInteractedDelegate OnHitTarget;
	FOnTargetInteractedDelegate OnPulledFromTarget;

protected:

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_Controller() override;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly, Category = "Collision")
	TObjectPtr <UBoxComponent> LeftHandCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	FName LeftHandCollisionBoxAttachBoneName;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr <UBoxComponent> RightHandCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	FName RightHandCollisionBoxAttachBoneName;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UHDBAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UHDBAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpData> CharacterStartUpData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	FORCEINLINE UHDBAbilitySystemComponent* GetHDBAbilitySystemComponent() const { return AbilitySystemComponent; }

	FORCEINLINE UHDBAttributeSet* GetHDBAttributeSet() const { return AttributeSet; }

	FORCEINLINE UBoxComponent* GetLeftHandCollisionBox() const { return LeftHandCollisionBox; }
	FORCEINLINE UBoxComponent* GetRightHandCollisionBox() const { return RightHandCollisionBox; }

};
