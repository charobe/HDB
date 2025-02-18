// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HDBAnimationAttackInterface.h"
#include "HDBCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class HDB_API AHDBCharacterBase : public ACharacter , public IHDBAnimationAttackInterface
{
	GENERATED_BODY()

public:
	AHDBCharacterBase();

protected:
	virtual void SetCharacterControlData(const class UHDBCharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UHDBCharacterControlData*> CharacterControlManager;

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
};
