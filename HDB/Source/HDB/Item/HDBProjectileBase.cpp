// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HDBProjectileBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"

AHDBProjectileBase::AHDBProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn,ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

}

void AHDBProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

