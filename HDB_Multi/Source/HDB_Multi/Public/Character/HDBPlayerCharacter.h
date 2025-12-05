// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HDBCharacterBase.h"
#include "GameplayTagContainer.h"
#include "HDBPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDA_InputConfig;
struct FInputActionValue;
class UPlayerCombatComponent;
/**
 * 
 */
UCLASS()
class HDB_MULTI_API AHDBPlayerCharacter : public AHDBCharacterBase
{
	GENERATED_BODY()

public:
	AHDBPlayerCharacter();

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_Controller() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDA_InputConfig* InputConfigDataAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UPlayerCombatComponent* CombatComponent;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

public:
	FORCEINLINE UPlayerCombatComponent* GetPlayerCombatComponent() const { return CombatComponent; }
};
