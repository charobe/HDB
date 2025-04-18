// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HDBPlayerWeapon.h"

void AHDBPlayerWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandle)
{
	GrantedAbilitySpecHandles = InSpecHandle;
}

TArray<FGameplayAbilitySpecHandle> AHDBPlayerWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
