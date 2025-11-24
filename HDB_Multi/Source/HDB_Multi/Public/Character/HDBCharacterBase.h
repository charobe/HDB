// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "HDBCharacterBase.generated.h"

class UHDBAbilitySystemComponent;
class UHDBAttributeSet;
class UBoxComponent;
class UDataAsset_StartUpData;

UCLASS()
class HDB_MULTI_API AHDBCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHDBCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

protected:

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_Controller() override;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly, Category = "Collision")
	TObjectPtr <UBoxComponent> LeftHandCollisionBox;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr <UBoxComponent> RightHandCollisionBox;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UHDBAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UHDBAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpData> CharacterStartUpData;

	UFUNCTION()
	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	FORCEINLINE UHDBAbilitySystemComponent* GetHDBAbilitySystemComponent() const { return AbilitySystemComponent; }

	FORCEINLINE UHDBAttributeSet* GetHDBAttributeSet() const { return AttributeSet; }

	FORCEINLINE UBoxComponent* GetLeftHandCollisionBox() const { return LeftHandCollisionBox; }
	FORCEINLINE UBoxComponent* GetRightHandCollisionBox() const { return RightHandCollisionBox; }

};
