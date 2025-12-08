// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HDBAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

#include "HDBDebugHelper.h"

UHDBAttributeSet::UHDBAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentHaza(1.f);
	InitMaxHaza(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UHDBAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
    {
        SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
    }
    else if (Data.EvaluatedData.Attribute == GetCurrentHazaAttribute())
    {
        SetCurrentHaza(FMath::Clamp(GetCurrentHaza(), 0.f, GetMaxHaza()));
    }
    else if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
    {
        const float OldHealth = GetCurrentHealth();
        const float DamageDone = GetDamageTaken();

        if (DamageDone > 0.f)
        {
            const float NewCurrentHealth =
                FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());

            SetCurrentHealth(NewCurrentHealth);

            const FString DebugString = FString::Printf(
                TEXT("Old Health: %f, Damage Done: %f, NewCurrentHealth: %f"),
                OldHealth, DamageDone, NewCurrentHealth
            );

            Debug::Print(DebugString, FColor::Green);

            if (NewCurrentHealth <= 0.f)
            {
            }
        }
        SetDamageTaken(0.f);
    }
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

void UHDBAttributeSet::OnRep_DamageTaken(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHDBAttributeSet, DamageTaken, OldValue);

}
