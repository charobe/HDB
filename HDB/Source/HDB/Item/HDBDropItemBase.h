// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HDBDropItemBase.generated.h"

class USphereComponent;

UCLASS()
class HDB_API AHDBDropItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AHDBDropItemBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pick UP Interaction")
	USphereComponent* CollisionSphere;

	UFUNCTION()
	virtual void OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
