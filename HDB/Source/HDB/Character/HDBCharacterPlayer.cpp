// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBCharacterPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "Components/HDBInputComponent.h"
#include "Tag/HDBGameplayTag.h"
#include "AbilitySystem/PlayerAbilitySystemComponent.h"
#include "DataAsset/DataAsset_PlayerStartUpData.h"
#include "Components/PlayerCombatComponent.h"
#include "Components/UI/PlayerUIComponent.h"

#include "HDB/HDBDebugHelper.h"


AHDBCharacterPlayer::AHDBCharacterPlayer()
{

	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 68.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("HDBCapsule"));

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.7f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollsion"));

	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 30.f);
	CameraBoom->bUsePawnControlRotation = true;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//Shader
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(1);

	//Combat
	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));

	PlayerUIComponent = CreateDefaultSubobject<UPlayerUIComponent>(TEXT("PlayerUIComponent"));

}

UPawnCombatComponent* AHDBCharacterPlayer::GetPawnCombatComponent() const
{
	return PlayerCombatComponent;
}

UPawnUIComponent* AHDBCharacterPlayer::GetUIComponent() const
{
	return PlayerUIComponent;
}

UPlayerUIComponent* AHDBCharacterPlayer::GetPlayerUIComponent() const
{
	return PlayerUIComponent;
}

void AHDBCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(PlayerAbilitySystemComponent);
		}
	}
	
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

	//slide
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();

	if (MoveComp) {
		if (MoveComp->Velocity.Size() < 10.f) {
			FVector AdjustedVelocity = MoveComp->Velocity.GetSafeNormal() * 5.f;
			MoveComp->Velocity = AdjustedVelocity;
		}

		MoveComp->BrakingFrictionFactor = 2.0f;
		MoveComp->BrakingDecelerationWalking = 400.f;
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

void AHDBCharacterPlayer::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	PlayerAbilitySystemComponent->OnAbilityInputPressed(InputTag);

}

void AHDBCharacterPlayer::Input_AbilityReleasedPressed(FGameplayTag InputTag)
{
	PlayerAbilitySystemComponent->OnAbilityInputReleased(InputTag);
}

void AHDBCharacterPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("input config에 적절한 데이터 에셋을 연결하지 않았음"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UHDBInputComponent* HDBInputComponent = CastChecked<UHDBInputComponent>(PlayerInputComponent);

	HDBInputComponent->BindNativeInputAction(InputConfigDataAsset, HDBGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	HDBInputComponent->BindNativeInputAction(InputConfigDataAsset, HDBGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	HDBInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityReleasedPressed);
}

