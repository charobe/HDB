// Fill out your copyright notice in the Description page of Project Settings.

#include "HDBFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/PlayerAbilitySystemComponent.h"

UPlayerAbilitySystemComponent* UHDBFunctionLibrary::NativeGetASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UPlayerAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
		
}

void UHDBFunctionLibrary::AddGameplayTagToActor(AActor* InActor, FGameplayTag TagToAdd)
{
	UPlayerAbilitySystemComponent*  ASC = NativeGetASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}

}

void UHDBFunctionLibrary::RemoveGameplayFromActor(AActor* InActor, FGameplayTag TagToRemove)
{
	UPlayerAbilitySystemComponent* ASC = NativeGetASCFromActor(InActor);

	if(ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UHDBFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UPlayerAbilitySystemComponent* ASC = NativeGetASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UHDBFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EHDBConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EHDBConfirmType::Yes : EHDBConfirmType::No;
}

 