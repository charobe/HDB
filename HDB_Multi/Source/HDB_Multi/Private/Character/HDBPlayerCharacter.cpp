// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAsset/Input/DA_InputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "HDBGameplayTag.h"
#include "Component/Input/HDBInputComponent.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"
#include "Component/PlayerCombatComponent.h"
#include "DataAsset/StartUpData/DataAsset_PlayerStartUpData.h"
#include "Component/PlayerUIComponent.h"

#include "HDBDebugHelper.h"

AHDBPlayerCharacter::AHDBPlayerCharacter()
{
	bReplicates = true;
	NetUpdateFrequency = 100.f;

	GetMesh()->SetIsReplicated(true);

	GetCapsuleComponent()->InitCapsuleSize(42.f, 68.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 30.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.7f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("CombatComponent"));
	PlayerUIComponent = CreateDefaultSubobject<UPlayerUIComponent>(TEXT("PlayerUIComponent"));

	OnHitTarget.BindUObject(CombatComponent, &UPlayerCombatComponent::OnHitTargetActor);
	OnPulledFromTarget.BindUObject(CombatComponent, &UPlayerCombatComponent::OnPulledFromTargetActor);
}

UPawnCombatComponent* AHDBPlayerCharacter::GetPawnCombatComponent() const
{
	return CombatComponent;
}

UPawnUIComponent* AHDBPlayerCharacter::GetPawnUIComponent() const
{
	return PlayerUIComponent;
}

UPlayerUIComponent* AHDBPlayerCharacter::GetPlayerUIComponent() const
{
	return nullptr;
}

void AHDBPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController || !PlayerController->IsLocalController())
	{
		return;
	}

	if (!InputConfigDataAsset)
	{
		return;
	}

	if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputConfigDataAsset->DefaultMappingContext)
			{
				Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
			}
		}
	}
	
	UHDBInputComponent* HDBInputComponent = Cast<UHDBInputComponent>(PlayerInputComponent);

	if (!HDBInputComponent)
	{
		return;
	}

	HDBInputComponent->BindNativeInputAction(InputConfigDataAsset, HDBGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	HDBInputComponent->BindNativeInputAction(InputConfigDataAsset, HDBGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	
	HDBInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

void AHDBPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpData* Data = CharacterStartUpData.LoadSynchronous())
		{
			Data->GiveToAbilitySystemComponent(AbilitySystemComponent);
		}
	}
}

void AHDBPlayerCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AHDBPlayerCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	if (!HasAuthority())
	{
		return;
	}

	APawn* OwningPawn = GetInstigator<APawn>();

	checkf(OwningPawn, TEXT("instigator 설정 오류: %s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (OwningPawn != HitPawn)
		{
			OnHitTarget.ExecuteIfBound(OtherActor);
		}
	}
}

void AHDBPlayerCharacter::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	if (!HasAuthority())
	{
		return;
	}

	APawn* OwningPawn = GetInstigator<APawn>();

	checkf(OwningPawn, TEXT("instigator 설정 오류: %s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (OwningPawn != HitPawn)
		{
			OnPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}

void AHDBPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
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

void AHDBPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHDBPlayerCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	AbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}


/*
void AHDBPlayerCharacter::AddFootprintTick()
{
	UWorld* World = GetWorld();
	if (!World) return;

	float CurrentTime = World->GetTimeSeconds();
	FVector FootprintLocation = GetActorLocation();

	//UE_LOG(LogTemp, Warning, TEXT("Footprint Location: %s"), *FootprintLocation.ToString());

	UFootprintManager::Get(World)->AddFootprint(FootprintLocation, CurrentTime); //get pos

	UFootprintManager::Get(World)->Update(CurrentTime, 7.0f);

}

*/

void AHDBPlayerCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	AbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

