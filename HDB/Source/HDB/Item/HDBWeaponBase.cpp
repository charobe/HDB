// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HDBWeaponBase.h"
#include "Components/BoxComponent.h"


AHDBWeaponBase::AHDBWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RightWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(RightWeaponMesh);

	LeftWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(LeftWeaponMesh);

	RightWeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	RightWeaponCollisionBox->SetupAttachment(GetRootComponent());
	RightWeaponCollisionBox->SetBoxExtent(FVector(20.f));
	RightWeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LeftWeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	LeftWeaponCollisionBox->SetupAttachment(GetRootComponent());
	LeftWeaponCollisionBox->SetBoxExtent(FVector(20.f));
	LeftWeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

