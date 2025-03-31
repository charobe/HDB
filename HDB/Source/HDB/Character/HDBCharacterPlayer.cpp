// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "HDBCharacterControlData.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "Components/HDBInputComponent.h"
#include "Tag/HDBGameplayTag.h"

#include "HDB/HDBDebugHelper.h"


AHDBCharacterPlayer::AHDBCharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Ghost = CreateDefaultSubobject<UBoxComponent>(TEXT("Ghost"));
	Ghost->SetupAttachment(RootComponent);

	//default Status
	Atk = 10;
	Def = 10;
	Spd = 10;
	HP = MaxHp;
	HazaStack_Mind = 0;

	//Shader
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(1);
}

void AHDBCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
		return;

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
		return;

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	if (!InputSubsystem)
		return;

	GetWorldTimerManager().SetTimer(GhostUpdate, this, &AHDBCharacterPlayer::UpdateGhost, GhostUpdateInterval, true);

	// Haza
	GetWorld()->GetTimerManager().SetTimer(HazaBodyTimerHandle, this, &AHDBCharacterPlayer::HazaBody, 5.0f, true);
	GetWorld()->GetTimerManager().SetTimer(HazaMindTimerHandle, this, &AHDBCharacterPlayer::HazaMind, 10.0f, true);

}

void AHDBCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GhostLocations.Add(GetActorLocation());

	if (GhostLocations.Num() > 60){
		GhostLocations.RemoveAt(0);
	}

}

bool AHDBCharacterPlayer::IsDead() const {
	return HP <= 0;
}

void AHDBCharacterPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("input config에 적절한 데이터 에셋을 연결하지 않았음"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	
	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext,0);

	UHDBInputComponent* HDBInputComponent = CastChecked<UHDBInputComponent>(PlayerInputComponent);

	HDBInputComponent->BindNativeInputAction(InputConfigDataAsset, HDBGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	HDBInputComponent->BindNativeInputAction(InputConfigDataAsset, HDBGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

}

float AHDBCharacterPlayer::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(HP, DamageToApply);
	HP -= DamageToApply;

	if (IsDead()) {
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}

	return DamageToApply;
}


void AHDBCharacterPlayer::SetCharacterControlData(const UHDBCharacterControlData* CharacterControlData)
{
	Super::SetCharacterControlData(CharacterControlData);

	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;

}


void AHDBCharacterPlayer::UpdateGhost() {
	if (GhostLocations.Num() > 0)
	{
		FVector OldestLocation = GhostLocations[0];
		Ghost->SetWorldLocation(OldestLocation);
	}
}

void AHDBCharacterPlayer::HazaBody() {
	int RandomStat = FMath::RandRange(0, 2);  // 0 = ATK, 1 = DEF

	switch (RandomStat) {
	case 0:
		Atk -= 1;
		UE_LOG(LogTemp, Warning, TEXT("Atk 하자"));
		break;
	case 1:
		Def -= 1;
		UE_LOG(LogTemp, Warning, TEXT("Def 하자"));
		break;
	}
	
}

void AHDBCharacterPlayer::HazaMind() {
	HazaStack_Mind += 1;

	HP -= HazaStack_Mind;

}

void AHDBCharacterPlayer::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AHDBCharacterPlayer::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2d>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
