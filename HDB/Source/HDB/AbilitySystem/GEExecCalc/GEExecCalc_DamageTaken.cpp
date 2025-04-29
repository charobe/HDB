// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "Tag/HDBGameplayTag.h"


struct FHDBDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)


	FHDBDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet,AttackPower,Source,false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet,DefensePower,Target,false)

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
	RelevantAttributesToCapture.Add(GetHDBDamageCapture().DefensePowerDef);

}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

    /*EffectSpec.GetContext().GetSourceObject();
    EffectSpec.GetContext().GetAbility();
    EffectSpec.GetContext().GetInstigator();
    EffectSpec.GetContext().GetEffectCauser();*/

    FAggregatorEvaluateParameters EvaluateParameters;
    EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
    EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

    float SourceAttackPower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetHDBDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

    float BaseDamage = 0.f;
    int32 UsedLightAttckComboCount = 0;
    int32 UsedHeavyAttackComboCount = 0;

    for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
    {
        if (TagMagnitude.Key.MatchesTagExact(HDBGameplayTags::Shared_SetByCaller_BaseDamage))
        {
            BaseDamage = TagMagnitude.Value;
        }

        if (TagMagnitude.Key.MatchesTagExact(HDBGameplayTags::Player_SetByCaller_AttackType_Light))
        {
            UsedLightAttckComboCount = TagMagnitude.Value;
        }

        if (TagMagnitude.Key.MatchesTagExact(HDBGameplayTags::Player_SetByCaller_AttackType_Heavy))
        {
            UsedHeavyAttackComboCount = TagMagnitude.Value;
        }
    }

    float TargetDefensePower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetHDBDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
}
