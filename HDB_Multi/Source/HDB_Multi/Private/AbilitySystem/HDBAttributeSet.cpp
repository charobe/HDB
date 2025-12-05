// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HDBAttributeSet.h"
#include "Net/UnrealNetwork.h"


UHDBAttributeSet::UHDBAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentHaza(1.f);
	InitMaxHaza(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UHDBAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHDBAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHDBAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHDBAttributeSet, CurrentHaza, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHDBAttributeSet, MaxHaza, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHDBAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHDBAttributeSet, DefensePower, COND_None, REPNOTIFY_Always);
}


void UHDBAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHDBAttributeSet, CurrentHealth, OldValue);
}

void UHDBAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHDBAttributeSet, MaxHealth, OldValue);
}

void UHDBAttributeSet::OnRep_CurrentHaza(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHDBAttributeSet, CurrentHaza, OldValue);
}

void UHDBAttributeSet::OnRep_MaxHaza(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHDBAttributeSet, MaxHaza, OldValue);
}

void UHDBAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHDBAttributeSet, AttackPower, OldValue);
}

void UHDBAttributeSet::OnRep_DefensePower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHDBAttributeSet, DefensePower, OldValue);
}
