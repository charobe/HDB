// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Wing.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

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

	// Get Owener
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (OwnerPawn == nullptr)
		return;

	AController* OwnerController = OwnerPawn->GetController();

	if (OwnerController == nullptr)
		return;

	//Setting Lotation and Rotation
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	// Feather range setting
	FVector End = Location + Rotation.Vector() * MaxRange;
	
	//LineTracing
	FHitResult Hit;

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);

	if (bSuccess) {
		//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);
		FVector ShotDirection = -Rotation.Vector();
		//UGameplayStatics::SpawnEmitterAtLocation();

		AActor* HitActor = Hit.GetActor();

		if (HitActor != nullptr) {
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);

			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);

		}
	}

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

