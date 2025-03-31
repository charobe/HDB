// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HDBAnimationAttackInterface.h"
#include "HDBCharacterBase.generated.h"

UCLASS()
class HDB_API AHDBCharacterBase : public ACharacter , public IHDBAnimationAttackInterface
{
	GENERATED_BODY()

public:
	AHDBCharacterBase();

protected:
	virtual void SetCharacterControlData(const class UHDBCharacterControlData* CharacterControlData);

// Combo Action Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	void ProcessComboCommand();

// Attack Hit Section

	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

// Dead Section

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;

	//default status
	UPROPERTY(EditDefaultsOnly)
	float MaxHp = 100;

	UPROPERTY(EditDefaultsOnly)
	float Atk = 100;

	UPROPERTY(EditDefaultsOnly)
	float Def = 100;

	UPROPERTY(EditDefaultsOnly)
	float Spd = 100;

	//haza status
	UPROPERTY(EditDefaultsOnly)
	float HazaStack_Body = 100;

	UPROPERTY(EditDefaultsOnly)
	float HazaStack_Mind = 100;

};
