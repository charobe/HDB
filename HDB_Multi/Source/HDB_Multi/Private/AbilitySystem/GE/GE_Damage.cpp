// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GE/GE_Damage.h
#include "AbilitySystem/HDBAttributeSet.h"
#include "HDBGameplayTag.h"

struct FHDBDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)

	FHDBDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHDBAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHDBAttributeSet, DefensePower, Target, false)
	}
};

static const FHDBDamageCapture& GetHDBDamageCapture()
{
	static FHDBDamageCapture DamageCapture;
	return DamageCapture;
}

UGE_Damage::UGE_Damage()
{
}
