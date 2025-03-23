// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HDBCharacterPlayer.h"
#include "AbilitySystemInterface.h"
#include "HDBGASCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API AHDBGASCharacterPlayer : public AHDBCharacterPlayer, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AHDBGASCharacterPlayer();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void SetupGASInputComponent();
	void GASInputPressed(int32 InputId);
	void GASInputReleased(int32 InputId);

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category=GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
};
