// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/HDBGASTree.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

AHDBGASTree::AHDBGASTree()
{
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
	return nullptr;
}

void AHDBGASTree::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	RotatingMovement->bAutoActivate = false;
	RotatingMovement->Deactivate();
}

void AHDBGASTree::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &AHDBGASTree::TimerAction, ActionPeriod, true, 0.0f);
	
}

void AHDBGASTree::TimerAction()
{
	UE_LOG(LogTemp, Log, TEXT("Begin"));

	if (!RotatingMovement->IsActive())
	{
		RotatingMovement->Activate(true);
	}
	else
	{
		RotatingMovement->Deactivate();
	}
}

