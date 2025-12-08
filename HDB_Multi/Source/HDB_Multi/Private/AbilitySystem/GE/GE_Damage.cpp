// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GE/GE_Damage.h"
#include "AbilitySystem/HDBAttributeSet.h"
#include "HDBGameplayTag.h"

#include "HDBDebugHelper.h"

struct FHDBDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken);


	FHDBDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHDBAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHDBAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHDBAttributeSet, DamageTaken, Target, false);

	}
};

static const FHDBDamageCapture& GetHDBDamageCapture()
{
	static FHDBDamageCapture DamageCapture;
	return DamageCapture;
}

UGE_Damage::UGE_Damage()
{
	RelevantAttributesToCapture.Add(GetHDBDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetHDBDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetHDBDamageCapture().DamageTakenDef);

}

void UGE_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
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

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(HDBGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(HDBGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttckComboCount = FMath::RoundToInt(TagMagnitude.Value);
		}
	}

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetHDBDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);

	if (UsedLightAttckComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttckComboCount - 1) * 0.05f + 1.f;

		BaseDamage *= DamageIncreasePercentLight;
		//Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage);
	}

	float FinalDamageDone = (BaseDamage + SourceAttackPower) - TargetDefensePower;
	FinalDamageDone = FMath::Max(0.f, FinalDamageDone);
	//Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);

	if(FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				UHDBAttributeSet::GetDamageTakenAttribute(),
				EGameplayModOp::Additive,
				FinalDamageDone
			)
		);
	}
}
