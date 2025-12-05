// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"
#include "HDBAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class HDB_MULTI_API UHDBAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UHDBAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Haza")
	FGameplayAttributeData CurrentHaza;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, CurrentHaza)

	UPROPERTY(BlueprintReadOnly, Category = "Haza")
	FGameplayAttributeData MaxHaza;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, MaxHaza)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, DefensePower)
};
