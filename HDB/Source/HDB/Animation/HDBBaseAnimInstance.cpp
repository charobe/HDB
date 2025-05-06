// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HDBBaseAnimInstance.h"
#include "HDBFunctionLibrary.h"

bool UHDBBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UHDBFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}