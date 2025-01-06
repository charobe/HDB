// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackBox.h"

// Sets default values
AAttackBox::AAttackBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAttackBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttackBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

