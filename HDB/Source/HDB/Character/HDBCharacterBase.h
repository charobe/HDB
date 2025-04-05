// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HDBCharacterBase.generated.h"

UCLASS()
class HDB_API AHDBCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AHDBCharacterBase();

protected:
	virtual void SetCharacterControlData(const class UHDBCharacterControlData* CharacterControlData);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<class UPlayerAbilitySystemComponent> PlayerAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<class UPlayerAttributeSet> PlayerAttributeSet;

public:
	FORCEINLINE UPlayerAbilitySystemComponent* GetPlayerAbilitySystemComponent() const { return PlayerAbilitySystemComponent; }
	FORCEINLINE UPlayerAttributeSet* GetPlayerAttributeSet() const {return PlayerAttributeSet;	}
};
