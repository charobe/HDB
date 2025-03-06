// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "NiagaraSystem.h"
#include "Character_Wing.generated.h"


UCLASS()
class HDB_API ACharacter_Wing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacter_Wing();

	void NormalAttack();

	void QSkill();

	void WSkill();

	void PerformWSkill();

	void ESkill();

	void RSkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* FeatherEffect;

	//range default value = 1000
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	//Q
	FTimerHandle QSkillTimerHandle;

	UPROPERTY(EditAnywhere)
	float QRange = 1500;

	UPROPERTY(EditAnywhere)
	float QDamage = 30;


	//W
	FTimerHandle WSkillTimerHandle;

	UPROPERTY(EditAnywhere)
	float WRange = 1000;

	UPROPERTY(EditAnywhere)
	float WDamage = 20;

	int WCount = 0;

	//E
	UPROPERTY(EditAnywhere)
	float ERange = 300;

	UPROPERTY(EditAnywhere)
	float EDamage = 50;

	//R
	FTimerHandle RSkillTimerHandle;

	UPROPERTY(EditAnywhere)
	float RRange = 3000;

	UPROPERTY(EditAnywhere)
	float RDamage = 300;

};
