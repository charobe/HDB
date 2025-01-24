// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestChar.generated.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestChar.generated.h"

UCLASS()
class HDB_API ATestChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestChar();

private:
	// IMC
	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputMappingContext* DefaultMappingContext;
	// IA_Jump
	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* JumpAction;
	// IA_Look
	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* LookAction;
	// IA_Move
	UPROPERTY(editanywhere, category = input, meta = (allowprivateaccess = true))
	class UInputAction* MoveAction;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Jump() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Ä«¸Þ¶ó
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* cameraComp;


};
