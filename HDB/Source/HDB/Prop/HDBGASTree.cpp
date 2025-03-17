// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/HDBGASTree.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GA/HDBGA_Rotate.h"

AHDBGASTree::AHDBGASTree()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotateMovement"));
	ActionPeriod = 3.0f;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Asset/Object/Tree/Tree01.Tree01'"));
	if (MeshRef.Object)
	{
	Mesh->SetStaticMesh(MeshRef.Object);
	}
}

UAbilitySystemComponent* AHDBGASTree::GetAbilitySystemComponent() const
{
	return ASC;
}

void AHDBGASTree::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	RotatingMovement->bAutoActivate = false;
	RotatingMovement->Deactivate();

	ASC->InitAbilityActorInfo(this, this);
	FGameplayAbilitySpec RotateSkillSpec(UHDBGA_Rotate::StaticClass());
	ASC->GiveAbility(RotateSkillSpec);
}

void AHDBGASTree::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &AHDBGASTree::TimerAction, ActionPeriod, true, 0.0f);
	
}

void AHDBGASTree::TimerAction()
{
	UE_LOG(LogTemp, Log, TEXT("Begin"));

	FGameplayAbilitySpec* RotateGASpec = ASC->FindAbilitySpecFromClass(UHDBGA_Rotate::StaticClass());
	if (!RotateGASpec)
	{
		UE_LOG(LogTemp, Error, TEXT("No Rotate Spec Found!"));
		return;
	}

	if (!RotateGASpec->IsActive())
	{
		ASC->TryActivateAbility(RotateGASpec->Handle);
	}
	else
	{
		ASC->CancelAbilityHandle(RotateGASpec->Handle);
	}

	//if (!RotatingMovement->IsActive())
	//{
	//	RotatingMovement->Activate(true);
	//}
	//else
	//{
	//	RotatingMovement->Deactivate();
	//}
}

