// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBBossCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

AHDBBossCharacter::AHDBBossCharacter() {
    PrimaryActorTick.bCanEverTick = true;

}

void AHDBBossCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (USkeletalMeshComponent* Mesh = GetMesh())
    {
        UMaterialInterface* BaseMaterial = Mesh->GetMaterial(0);
        DeformMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
        Mesh->SetMaterial(0, DeformMaterial);

    }
}

void AHDBBossCharacter::Tick(float Deltatime) {

}