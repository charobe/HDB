// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBCharacterBase.h"
#include "HDBCharacterControlData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/PlayerAbilitySystemComponent.h"
#include "AbilitySystem/PlayerAttributeSet.h"

// Sets default values
AHDBCharacterBase::AHDBCharacterBase()
{
	PlayerAbilitySystemComponent = CreateDefaultSubobject<UPlayerAbilitySystemComponent>(TEXT("PlayerAbilitySystemComponent"));

	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
}

UAbilitySystemComponent* AHDBCharacterBase::GetAbilitySystemComponent() const
{
	return GetPlayerAbilitySystemComponent();
}

void AHDBCharacterBase::SetCharacterControlData(const UHDBCharacterControlData* CharacterControlData)
{
	// 폰 섹션과 무브먼트 섹션에 관련된 데이터들을 설정

	// Pawn 
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

	//CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
}

void AHDBCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (PlayerAbilitySystemComponent)
	{
		PlayerAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("스타트 데이터 설정이 안되어 있음. %s"), *GetName());
	}
	
}
