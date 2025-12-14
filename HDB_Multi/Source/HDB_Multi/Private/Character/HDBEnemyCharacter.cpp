// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "Component/EnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widget/HDBWidgetBase.h"
#include "DataAsset/StartUpData/DataAsset_EnemyStartUpData.h"

AHDBEnemyCharacter::AHDBEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>("EnemyUIComponent");
	EnemyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyWidgetComponent");
	EnemyWidgetComponent->SetupAttachment(GetMesh());
	bReplicates = true;
	GetMesh()->SetIsReplicated(true);
}

UPawnCombatComponent* AHDBEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AHDBEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AHDBEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AHDBEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UHDBWidgetBase* Widget = Cast<UHDBWidgetBase>(EnemyWidgetComponent->GetUserWidgetObject()))
	{
		Widget->InitEnemyCreatedWidget(this);
	}
}

void AHDBEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void AHDBEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
	{
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartUpData* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(AbilitySystemComponent);
				}
			}
		)
	);
}
