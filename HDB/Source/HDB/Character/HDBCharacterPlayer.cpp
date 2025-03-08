// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBCharacterPlayer.h"
#include "Character_Wing.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "HDBCharacterControlData.h"
#include "Components/CapsuleComponent.h"

AHDBCharacterPlayer::AHDBCharacterPlayer()
{
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Input
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HDB/Input/Actions/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputChangeActionControlRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HDB/Input/Actions/IA_Change_Control.IA_Change_Control'"));
	if (nullptr != InputChangeActionControlRef.Object)
	{
		ChangeControlAction = InputChangeActionControlRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HDB/Input/Actions/IA_ShoulderMove.IA_ShoulderMove'"));
	if (nullptr != InputActionShoulderMoveRef.Object)
	{
		ShoulderMoveAction = InputActionShoulderMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HDB/Input/Actions/IA_ShoulderLook.IA_ShoulderLook'"));
	if (nullptr != InputActionShoulderLookRef.Object)
	{
		ShoulderLookAction = InputActionShoulderLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionQuaterMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HDB/Input/Actions/IA_QuaterMove.IA_QuaterMove'"));
	if (nullptr != InputActionQuaterMoveRef.Object)
	{
		QuaterMoveAction = InputActionQuaterMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionWingNormalAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HDB/Input/Actions/IA_WingAttack.IA_WingAttack'"));
	if (nullptr != InputActionWingNormalAttackRef.Object) {
		WingNormalAttack = InputActionWingNormalAttackRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/HDB/Input/Actions/IA_Attack.IA_Attack'"));
	if (nullptr != InputActionAttackRef.Object) {
		AttackAction = InputActionAttackRef.Object;
	}


	CurrentCharacterControlType = ECharacterControlType::Quater;
}

void AHDBCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;

	SetCharacterControl(CurrentCharacterControlType);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
		return;

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
		return;

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	if (!InputSubsystem)
		return;

	if (IMC_Shoulder)
		InputSubsystem->AddMappingContext(IMC_Shoulder, 0);


	Wing = GetWorld()->SpawnActor<ACharacter_Wing>(WingClass);

	Wing->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Wing_Socket"));
	Wing->SetOwner(this);

}

bool AHDBCharacterPlayer::IsDead() const {
	return HP <= 0;
}

void AHDBCharacterPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(ChangeControlAction, ETriggerEvent::Triggered, this, &AHDBCharacterPlayer::ChangeCharacterControl);
	EnhancedInputComponent->BindAction(ShoulderMoveAction, ETriggerEvent::Triggered, this, &AHDBCharacterPlayer::ShoulderMove);
	EnhancedInputComponent->BindAction(ShoulderLookAction, ETriggerEvent::Triggered, this, &AHDBCharacterPlayer::ShoulderLook);
	EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &AHDBCharacterPlayer::QuaterMove);

	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AHDBCharacterPlayer::Attack);
	EnhancedInputComponent->BindAction(IA_WingAttack, ETriggerEvent::Triggered, this, &AHDBCharacterPlayer::Shot);

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

// 현재 캐릭터 컨트롤 타입의 ENUM 값을 보고 반대쪽 ENUM값으로 변경
void AHDBCharacterPlayer::ChangeCharacterControl()
{
	if (CurrentCharacterControlType == ECharacterControlType::Quater)
	{
		SetCharacterControl(ECharacterControlType::Shoulder);
	}
	else if (CurrentCharacterControlType == ECharacterControlType::Shoulder)
	{
		SetCharacterControl(ECharacterControlType::Quater);
	}
}

void AHDBCharacterPlayer::SetCharacterControl(ECharacterControlType NewCharacterControlType)
{
	UHDBCharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType];
	check(NewCharacterControl);

	SetCharacterControlData(NewCharacterControl);

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
		if (NewMappingContext)
		{
			Subsystem->AddMappingContext(NewMappingContext, 0);
		}
	}

	CurrentCharacterControlType = NewCharacterControlType;
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

void AHDBCharacterPlayer::ShoulderMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AHDBCharacterPlayer::ShoulderLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AHDBCharacterPlayer::QuaterMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	float InputSizeSquared = MovementVector.SquaredLength();
	float MovementVectorSize = 1.0f;
	float MovementVectorSizeSquared = MovementVector.SquaredLength();
	if (MovementVectorSizeSquared > 1.0f)
	{
		MovementVector.Normalize();
		MovementVectorSizeSquared = 1.0f;
	}
	else
	{
		MovementVectorSize = FMath::Sqrt(MovementVectorSizeSquared);
	}

	FVector MoveDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);
	GetController()->SetControlRotation(FRotationMatrix::MakeFromX(MoveDirection).Rotator());
	AddMovementInput(MoveDirection, MovementVectorSize);
}

void AHDBCharacterPlayer::Shot(const FInputActionValue& value) {
	UE_LOG(LogTemp, Warning, TEXT("Shot function called!"));

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) {
		UE_LOG(LogTemp, Warning, TEXT("Pc is nullptr!"));
		return;
	}

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer){
		UE_LOG(LogTemp, Warning, TEXT("Lc is nullptr!"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	if (!InputSubsystem) {
		UE_LOG(LogTemp, Warning, TEXT("inputsub is nullptr!"));
		return;
	}

	if (!Wing) {
		UE_LOG(LogTemp, Warning, TEXT("Wing is nullptr!"));
		return;
	}

	TArray<FKey> PressedKeys = InputSubsystem->QueryKeysMappedToAction(IA_WingAttack);

	if (PressedKeys.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("No keys"));
		return;
	}

	FKey PressedKey = PressedKeys[0];

	UE_LOG(LogTemp, Warning, TEXT("Processed Key: %s"), *PressedKey.GetDisplayName().ToString());

	if (PressedKey == EKeys::LeftMouseButton) {
		Wing->NormalAttack();	
	}
	else if (PressedKey == EKeys::One) {
		Wing->QSkill();
	}
	else if (PressedKey == EKeys::Two) {
		Wing->WSkill();
	}
	else if (PressedKey == EKeys::Three) {
		Wing->ESkill();
	}
	else if (PressedKey == EKeys::Four) {
		Wing->RSkill();
	}


}

void AHDBCharacterPlayer::Attack()
{
	ProcessComboCommand();
}
