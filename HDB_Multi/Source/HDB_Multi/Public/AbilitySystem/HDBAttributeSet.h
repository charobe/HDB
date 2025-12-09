// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/HDBAbilitySystemComponent.h"
#include "HDBAttributeSet.generated.h"

class IPawnUIInterface;

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

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_CurrentHealth)
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Haza", ReplicatedUsing = OnRep_CurrentHaza)
	FGameplayAttributeData CurrentHaza;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, CurrentHaza)

	UPROPERTY(BlueprintReadOnly, Category = "Haza", ReplicatedUsing = OnRep_MaxHaza)
	FGameplayAttributeData MaxHaza;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, MaxHaza)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_DefensePower)
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_DamageTaken)
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UHDBAttributeSet, DamageTaken)

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION() 
	void OnRep_CurrentHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION() 
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION() 
	void OnRep_CurrentHaza(const FGameplayAttributeData& OldValue);

	UFUNCTION() 
	void OnRep_MaxHaza(const FGameplayAttributeData& OldValue);

	UFUNCTION() 
	void OnRep_AttackPower(const FGameplayAttributeData& OldValue);

	UFUNCTION() 
	void OnRep_DefensePower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_DamageTaken(const FGameplayAttributeData& OldValue);


private:
	TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;
	void BroadcastCurrentHealthRatio() const;
	void BroadcastCurrentHazaRatio() const;
};
