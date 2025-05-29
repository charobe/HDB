// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_TargetLock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/HDBCharacterPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/HDBWidgetBase.h"
#include "Player/HDBPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "HDBFunctionLibrary.h"
#include "Tag/HDBGameplayTag.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/PlayerAbilitySystemComponent.h"


#include "HDBDebugHelper.h"

void UGA_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	LockOnTarget();
	if (CurrentLockedActor)
	{
		InitTargetLockMovement();
		InitTargetLockMappingContext();
	}
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMovement();
	ResetTargetLockMappingContext();
	CleanArray();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_TargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor 
	|| 	UHDBFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor,HDBGameplayTags::Shared_Status_Death) || UHDBFunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), HDBGameplayTags::Shared_Status_Death))
	{
		CancelTargetLock();
		return;
	}

	SetTargetLockWidgetPosition();

	const bool bOverrideRotation = !UHDBFunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), HDBGameplayTags::Player_Status_Dash);
	if (bOverrideRotation)
	{
		FRotator LookAtRot =UKismetMathLibrary::FindLookAtRotation(
			GetPlayerCharacterFromActorInfo()->GetActorLocation(),
			CurrentLockedActor->GetActorLocation()
		);

		LookAtRot -= FRotator(CameraOffset, 0.f, 0.f);

		const FRotator CurrentRot = GetPlayerControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentRot, LookAtRot, DeltaTime, RotationInterpSpeed);
		
		GetPlayerControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
		GetPlayerCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	
	}
}

void UGA_TargetLock::SwitchTarget(const FGameplayTag& Tag)
{
	GetActorsToLock();
	
	TArray<AActor*> OnLeftActors;
	TArray<AActor*> OnRightActors;
	AActor* NewTarget = nullptr;

	GetActorsAroundTarget(OnLeftActors,OnRightActors);

	if (Tag == HDBGameplayTags::Player_Event_SwitchTarget_Left)
	{
		NewTarget = GetNearestTarget(OnLeftActors);
	}
	else 
	{
		NewTarget = GetNearestTarget(OnRightActors);
	}

	if (NewTarget)
	{
		CurrentLockedActor = NewTarget;
	}
}

void UGA_TargetLock::LockOnTarget()
{
	GetActorsToLock();

	if (ActorsToLock.IsEmpty())
	{
		CancelTargetLock();
		return;
	}
	CurrentLockedActor = GetNearestTarget(ActorsToLock);

	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();

		SetTargetLockWidgetPosition();
	}
	else
	{
		CancelTargetLock();
	}
}

void UGA_TargetLock::GetActorsToLock()
{
	ActorsToLock.Empty();
	TArray<FHitResult> BoxTraceHit;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() + GetPlayerCharacterFromActorInfo()->GetActorForwardVector() * TraceDistance,
		TraceBoxSize / 2.f,
		GetPlayerCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHit,
		true
	);

	for (const FHitResult& TraceHit : BoxTraceHit)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != GetPlayerCharacterFromActorInfo())
			{
				ActorsToLock.AddUnique(HitActor);
			}
		}
	}
}

AActor* UGA_TargetLock::GetNearestTarget(const TArray<AActor*>& InActors)
{
	float Distance = 0.f;
	AActor* NearestActor = UGameplayStatics::FindNearestActor(GetPlayerCharacterFromActorInfo()->GetActorLocation(), InActors, Distance);	
	return NearestActor;
}

void UGA_TargetLock::GetActorsAroundTarget(TArray<AActor*>& OnLeftActor, TArray<AActor*>& OnRightActor)
{
	if (!CurrentLockedActor || ActorsToLock.IsEmpty())
	{
		CancelTargetLock();
		return;
	}

	const FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	const FVector NormalizedPlayerToCurrentTarget = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

	for (AActor* Actor : ActorsToLock)
	{
		if (!Actor || Actor == CurrentLockedActor)
		{
			continue;
		}
		const FVector NormalizedPlayerToAvailable = (Actor->GetActorLocation() - PlayerLocation).GetSafeNormal();
		const FVector CrossResult = FVector::CrossProduct(NormalizedPlayerToCurrentTarget, NormalizedPlayerToAvailable);

		if (CrossResult.Z > 0.f)
		{
			OnRightActor.AddUnique(Actor);
		}
		else
		{
			OnLeftActor.AddUnique(Actor);
		}
	}
}

void UGA_TargetLock::DrawTargetLockWidget()
{
	if (!TargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("유효한 위젯 클래스가 없음."));

		TargetLockWidget = CreateWidget<UHDBWidgetBase>(GetPlayerControllerFromActorInfo(), TargetLockWidgetClass);

		check(TargetLockWidget);

		TargetLockWidget->AddToViewport(); 
	}
	
}

void UGA_TargetLock::SetTargetLockWidgetPosition()
{
	if (!TargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLock();
		return;
	}

	FVector2D ScreenPosition;

	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetPlayerControllerFromActorInfo(),
		CurrentLockedActor->GetActorLocation(),
		ScreenPosition,
		true
	);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		TargetLockWidget->WidgetTree->ForEachWidget(
			[this](UWidget* Widget)
			{
				if (USizeBox* SizeBox = Cast<USizeBox>(Widget))
				{
					TargetLockWidgetSize.X = SizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = SizeBox->GetHeightOverride();
				}
			}
		);
	}

	ScreenPosition -= (TargetLockWidgetSize / 2.f);


	TargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UGA_TargetLock::InitTargetLockMovement()
{
	if (ACharacter* Character = GetPlayerCharacterFromActorInfo())
	{
		if (UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement())
		{
			if (PlayerMaxWalkSpeed <= 0.f) 
			{
				PlayerMaxWalkSpeed = MoveComp->MaxWalkSpeed;
			}
			MoveComp->MaxWalkSpeed = TargetLockMaxWalkSpeed;
		}
	}
}

void UGA_TargetLock::InitTargetLockMappingContext()
{
	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(SubSystem);

	SubSystem->AddMappingContext(TargetLockMappingContext, 3);
}

void UGA_TargetLock::CancelTargetLock()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UGA_TargetLock::CleanArray()
{
	ActorsToLock.Empty();
	CurrentLockedActor = nullptr;

	if (TargetLockWidget)
	{
		TargetLockWidget->RemoveFromParent();
	}
	TargetLockWidget = nullptr;

	TargetLockWidgetSize = FVector2D::ZeroVector;
	PlayerMaxWalkSpeed = 0.f;
}

void UGA_TargetLock::ResetTargetLockMovement()
{
	if (ACharacter* Character = GetPlayerCharacterFromActorInfo())
	{
		if (UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement())
		{
			MoveComp->MaxWalkSpeed = PlayerMaxWalkSpeed > 0.f ? PlayerMaxWalkSpeed :500.f;
		}
		PlayerMaxWalkSpeed = 0.f;
	}
}

void UGA_TargetLock::ResetTargetLockMappingContext()
{
	if (!GetPlayerControllerFromActorInfo())
	{
		return;
	}

	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(SubSystem);

	SubSystem->RemoveMappingContext(TargetLockMappingContext);
}
