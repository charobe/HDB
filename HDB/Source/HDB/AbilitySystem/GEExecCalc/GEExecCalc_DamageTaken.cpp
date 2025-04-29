// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/PlayerAttributeSet.h"

struct FHDBDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)

	FHDBDamageCapture()
	{
		DECLARE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet,AttackPower,Source,false)
	}
};

static const FHDBDamageCapture& GetHDBDamageCapture()
{
	static FHDBDamageCapture HDBDamageCapture;
	return HDBDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	// 캡처 하는 법 1
	//FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	//	UPlayerAttributeSet::StaticClass(),
	//	GET_MEMBER_NAME_CHECKED(UPlayerAttributeSet, AttackPower)
	//);

	//FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	//	AttackPowerProperty,
	//	EGameplayEffectAttributeCaptureSource::Source,
	//	false
	//);
	
	//RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);
	RelevantAttributesToCapture.Add(GetHDBDamageCapture().AttackPowerDef);
}
