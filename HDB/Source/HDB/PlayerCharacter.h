// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class ACharacter_Wing;

UCLASS()
class HDB_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void HandleDistruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SkillSpawnPoint;

	UPROPERTY(EditAnywhere)
	float Speed = 200.f;

	// IMC
	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* MoveAction;

	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* JumpAction;

	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* LookAction;


	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Jump() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacter_Wing> WingClass;

	UPROPERTY()
	ACharacter_Wing* Wing;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
