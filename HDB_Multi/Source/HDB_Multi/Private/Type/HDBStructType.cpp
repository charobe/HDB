// Fill out your copyright notice in the Description page of Project Settings.


#include "Type/HDBStructType.h"
#include "AbilitySystem/Ability/PlayerGameplayAbility.h"

bool FHDBPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}