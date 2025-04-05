// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HDBWeaponBase.generated.h"

UCLASS()
class HDB_API AHDBWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHDBWeaponBase();
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* RightWeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* LeftWeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	TObjectPtr<class UBoxComponent> RightWeaponCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	TObjectPtr<class UBoxComponent> LeftWeaponCollisionBox;


public:
	FORCEINLINE UBoxComponent* GetRightWeaponCollisionBox() const { return RightWeaponCollisionBox; }
	FORCEINLINE UBoxComponent* GetLeftWeaponCollisionBox() const { return LeftWeaponCollisionBox; }

};
