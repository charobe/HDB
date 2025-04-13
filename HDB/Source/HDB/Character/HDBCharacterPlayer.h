// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HDBCharacterBase.h"
#include "GameplayTagContainer.h"
#include "HDBCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API AHDBCharacterPlayer : public AHDBCharacterBase
{
	GENERATED_BODY()
	
public:
	AHDBCharacterPlayer();

protected: 
	void PossessedBy(AController* NewController) override;

	virtual void BeginPlay() override;

// Character Control Section
protected:
	virtual void SetCharacterControlData(const class UHDBCharacterControlData* CharacterControlData) override;

// Camera Section

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

// Combat Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPlayerCombatComponent> PlayerCombatComponent;

private:
	// Input Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDataAsset_InputConfig> InputConfigDataAsset;

	void Input_Move(const struct FInputActionValue& InputActionValue);
	void Input_Look(const struct FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InputTag);
	void Input_AbilityReleasedPressed(FGameplayTag InputTag);

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FORCEINLINE UPlayerCombatComponent* GetPlayerCombatComponent() const { return PlayerCombatComponent; }

	UPROPERTY(BlueprintReadWrite, Category = "CharacterForm")
	FGameplayTag CurrentCharacterForm;

};
