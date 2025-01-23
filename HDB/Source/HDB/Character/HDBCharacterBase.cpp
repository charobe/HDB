// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBCharacterBase.h"

// Sets default values
AHDBCharacterBase::AHDBCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHDBCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHDBCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHDBCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

