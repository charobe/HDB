// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBCharacterBase.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"
#include "AbilitySystem/HDBAttributeSet.h"

// Sets default values
AHDBCharacterBase::AHDBCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	AbilitySystemComponent = CreateDefaultSubobject<UHDBAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UHDBAttributeSet>(TEXT("AttributeSet"));

}

UAbilitySystemComponent* AHDBCharacterBase::GetAbilitySystemComponent() const
{
	return GetHDBAbilitySystemComponent();
}


void AHDBCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}


