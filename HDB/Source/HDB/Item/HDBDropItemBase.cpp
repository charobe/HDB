// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HDBDropItemBase.h"
#include "Components/SphereComponent.h"

// Sets default values
AHDBDropItemBase::AHDBDropItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollisionSphere"));
	SetRootComponent(CollisionSphere);
	CollisionSphere->InitSphereRadius(50.f);
	CollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this,&ThisClass::OnCollisionSphereBeginOverlap);
}

void AHDBDropItemBase::OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}



