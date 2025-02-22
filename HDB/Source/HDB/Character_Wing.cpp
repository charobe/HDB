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
	UE_LOG(LogTemp, Warning, TEXT("Normal Shooting"));
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
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

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

void ACharacter_Wing::QSkill() {
	UE_LOG(LogTemp, Warning, TEXT("Q Ready"));

	GetWorld()->GetTimerManager().SetTimer(QSkillTimerHandle, [this]() {
		UE_LOG(LogTemp, Warning, TEXT("Q Shooting"));

		// Get Owner
		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (OwnerPawn == nullptr)
			return;

		AController* OwnerController = OwnerPawn->GetController();
		if (OwnerController == nullptr)
			return;

		// Get player viewpoint
		FVector Location;
		FRotator Rotation;
		OwnerController->GetPlayerViewPoint(Location, Rotation);

		//5 feather fanshape with 10 angle
		const TArray<float> Angles = { -20, -10, 0, 10, 20 };

		for (float AngleOffset : Angles) {
			FRotator AdjustedRotation = Rotation + FRotator(0, AngleOffset, 0);
			FVector End = Location + AdjustedRotation.Vector() * QRange;

			FHitResult Hit;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			Params.AddIgnoredActor(GetOwner());

			bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

			if (bSuccess) {
				FVector ShotDirection = -AdjustedRotation.Vector();
				AActor* HitActor = Hit.GetActor();
				if (HitActor) {
					FPointDamageEvent DamageEvent(QDamage, Hit, ShotDirection, nullptr);
					HitActor->TakeDamage(QDamage, DamageEvent, OwnerController, this);
				}
			}
		}

	}, 1.0f, false);

}

void ACharacter_Wing::ESkill() {
	UE_LOG(LogTemp, Warning, TEXT("E Shooting"));

	// Get Owner
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (OwnerPawn == nullptr)
		return;

	AController* OwnerController = OwnerPawn->GetController();

	if (OwnerController == nullptr)
		return;

	// Setting Location and Rotation
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	//60도 아래를 공격함
	Rotation.Pitch -= 60.0f;

	// Feather range setting
	FVector End = Location + Rotation.Vector() * ERange;

	// LineTracing
	FHitResult Hit;
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

	if (bSuccess && Hit.GetActor()) {
		FVector ShotDirection = -Rotation.Vector();
		AActor* HitActor = Hit.GetActor();

		// Ensure a valid hit component
		FPointDamageEvent DamageEvent(EDamage, Hit, ShotDirection, nullptr);

		HitActor->TakeDamage(EDamage, DamageEvent, OwnerController, this);

		UE_LOG(LogTemp, Warning, TEXT("Hit Actor"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Missed Shot"));
	}

	// Smooth backward movement (Jump effect)
	FVector BackwardOffset = -GetActorForwardVector() * 300.0f;
	//LaunchCharacter(BackwardOffset, true, false);

}

void ACharacter_Wing::RSkill() {
	UE_LOG(LogTemp, Warning, TEXT("R Shooting"));
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
	FVector End = Location + Rotation.Vector() * RRange;

	//LineTracing
	FHitResult Hit;
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	float TraceRadius = 50.0; // 두께

	bool bSuccess = GetWorld()->SweepSingleByChannel(Hit, Location, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(TraceRadius), Params);

	if (bSuccess) {
		//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);
		FVector ShotDirection = -Rotation.Vector();
		//UGameplayStatics::SpawnEmitterAtLocation();

		AActor* HitActor = Hit.GetActor();

		if (HitActor != nullptr) {
			FPointDamageEvent DamageEvent(RDamage, Hit, ShotDirection, nullptr);

			HitActor->TakeDamage(RDamage, DamageEvent, OwnerController, this);

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

