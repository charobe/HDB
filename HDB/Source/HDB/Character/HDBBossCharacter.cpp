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

    USkeletalMeshComponent* SkeletalMeshComp = GetMesh();
    if (SkeletalMeshComp)
    {
        UMaterialInterface* BaseMaterial = SkeletalMeshComp->GetMaterial(0);
        if (BaseMaterial)
        {
            DeformMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
            SkeletalMeshComp->SetMaterial(0, DeformMaterial);
        }
    }
}

void AHDBBossCharacter::ApplyImpactDeform(const FVector& HitLocation, float Strength)
{
    if (!DeformMaterial) return;

    ImpactLocation = HitLocation;
    ImpactStrength = Strength;
    TimeSinceImpact = 0.f;
    bDeforming = true;

    DeformMaterial->SetVectorParameterValue("ImpactLocation", ImpactLocation);
    DeformMaterial->SetScalarParameterValue("ImpactStrength", ImpactStrength);
    DeformMaterial->SetScalarParameterValue("ImpactRadius", ImpactRadius);
    DeformMaterial->SetScalarParameterValue("TimeSinceImpact", TimeSinceImpact);
}

void AHDBBossCharacter::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    if (bDeforming && DeformMaterial)
    {
        TimeSinceImpact += DeltaTime;
        DeformMaterial->SetScalarParameterValue("TimeSinceImpact", TimeSinceImpact);

        if (TimeSinceImpact >= RecoveryDuration)
        {
            bDeforming = false;
            DeformMaterial->SetScalarParameterValue("ImpactStrength", 0.f);
        }
    }
}