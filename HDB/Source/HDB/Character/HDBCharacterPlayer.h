// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/HDBCharacterBase.h"
#include "InputActionValue.h"
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
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

// Character Control Section
protected:
	virtual void SetCharacterControlData(const class UHDBCharacterControlData* CharacterControlData) override;

// Camera Section

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

private:
	//follow
	TArray<FVector> GhostLocations;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Ghost; 
	
	UPROPERTY(EditAnywhere)
	float GhostUpdateInterval = 1.0f;

	FTimerHandle GhostUpdate;

	void UpdateGhost();


	//stat
	UPROPERTY(VisibleAnywhere)
	float HP;

	FTimerHandle HazaBodyTimerHandle;
	void HazaBody();

	FTimerHandle HazaMindTimerHandle;
	void HazaMind();

private:
// Input Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDataAsset_InputConfig> InputConfigDataAsset;

	void Input_Move(const struct FInputActionValue& InputActionValue);
	void Input_Look(const struct FInputActionValue& InputActionValue);

};
