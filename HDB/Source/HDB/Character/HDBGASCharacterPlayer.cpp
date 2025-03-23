// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBGASCharacterPlayer.h"
#include "AbilitySystemComponent.h"
#include "Player/HDBGASPlayerState.h"
#include "EnhancedInputComponent.h"

AHDBGASCharacterPlayer::AHDBGASCharacterPlayer()
{
	ASC = nullptr;
}


UAbilitySystemComponent* AHDBGASCharacterPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

void AHDBGASCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AHDBGASPlayerState* GASPS = GetPlayerState<AHDBGASPlayerState>();
	if (GASPS)
	{
		ASC = GASPS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(GASPS, this);

		int32 InputId = 0;
		for (const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			StartSpec.InputID = InputId++;
			ASC->GiveAbility(StartSpec);

			SetupGASInputComponent();
		}
	}
}

void AHDBGASCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	SetupGASInputComponent();

}

void AHDBGASCharacterPlayer::SetupGASInputComponent()
{
	if (IsValid(ASC) && IsValid(InputComponent))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AHDBGASCharacterPlayer::GASInputPressed, 0);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AHDBGASCharacterPlayer::GASInputReleased, 0);
	}

}

void AHDBGASCharacterPlayer::GASInputPressed(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

void AHDBGASCharacterPlayer::GASInputReleased(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = false;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputReleased(*Spec);
		}
	}

}
