// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Wing.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACharacter_Wing::ACharacter_Wing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}


void ACharacter_Wing::NormalAttack() {
	// UGameplayStatics::SpawnEmitterAttached(FeatherEffect, Mesh, TEXT(""));
}

// Called when the game starts or when spawned
void ACharacter_Wing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_Wing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

