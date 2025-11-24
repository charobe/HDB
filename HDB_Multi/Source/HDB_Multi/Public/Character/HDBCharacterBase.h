// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "HDBCharacterBase.generated.h"

class UHDBAbilitySystemComponent;
class UHDBAttributeSet;

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

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UHDBAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UHDBAttributeSet> AttributeSet;

public:
	FORCEINLINE UHDBAbilitySystemComponent* GetHDBAbilitySystemComponent() const { return AbilitySystemComponent; }

	FORCEINLINE UHDBAttributeSet* GetHDBAttributeSet() const { return AttributeSet; }
};
