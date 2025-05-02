// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/PawnCombatInterface.h"
#include "Interface/PawnUIInterface.h"
#include "HDBCharacterBase.generated.h"

UCLASS()
class HDB_API AHDBCharacterBase : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	AHDBCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	virtual UPawnUIComponent* GetUIComponent() const override;


protected:

	// Ability System

	void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<class UPlayerAbilitySystemComponent> PlayerAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<class UPlayerAttributeSet> PlayerAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<class UDataAsset_StartUpDataBase> CharacterStartUpData;

public:
	FORCEINLINE UPlayerAbilitySystemComponent* GetPlayerAbilitySystemComponent() const { return PlayerAbilitySystemComponent; }
	FORCEINLINE UPlayerAttributeSet* GetPlayerAttributeSet() const {return PlayerAttributeSet;	}
};
