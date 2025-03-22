// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HDBGASPlayerState.h"
#include "AbilitySystemComponent.h"

AHDBGASPlayerState::AHDBGASPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	//ASC->SetIsReplicated(true);
}

UAbilitySystemComponent* AHDBGASPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
