// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HDBGASTree.generated.h"

UCLASS()
class HDB_API AHDBGASTree : public AActor
{
	GENERATED_BODY()
	
public:	
	AHDBGASTree();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	virtual void TimerAction();

protected:
	UPROPERTY(VisibleAnywhere, Category = Movement)
	TObjectPtr<class URotatingMovementComponent> RotatingMovement;

	UPROPERTY(EditAnywhere, Category = Timer)
	float ActionPeriod;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	FTimerHandle ActionTimer;
};
