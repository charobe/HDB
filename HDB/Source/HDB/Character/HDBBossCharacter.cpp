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

    USkeletalMeshComponent* GMesh = GetMesh();

    int32 HeadMaterialIndex = 3;
    int32 GolemMaterialIndex = 2;
    int32 BrickMaterialIndex = 0;

    UMaterialInstanceDynamic* DynMatHead = GMesh->CreateAndSetMaterialInstanceDynamic(HeadMaterialIndex);
    UMaterialInstanceDynamic* DynMatGolem = GMesh->CreateAndSetMaterialInstanceDynamic(GolemMaterialIndex);
    UMaterialInstanceDynamic* DynMatBrick = GMesh->CreateAndSetMaterialInstanceDynamic(BrickMaterialIndex);


    if (DynMatHead) {
        DynMatHead->SetVectorParameterValue("HeadColor", FLinearColor::Red);
    }
    if (DynMatGolem) {
        DynMatGolem->SetVectorParameterValue("HeadColor", FLinearColor::Red);
    }
    if (DynMatBrick) {
        DynMatBrick->SetVectorParameterValue("HeadColor", FLinearColor::Red);
    }


    UMaterialInterface* BaseMaterial = GetMesh()->GetMaterial(0);

    DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);

    if (DynamicMaterial)
    {
        GetMesh()->SetMaterial(0, DynamicMaterial);

        FVector BoneLocation = GetMesh()->GetBoneLocation(TargetBoneName, EBoneSpaces::WorldSpace);
        DynamicMaterial->SetVectorParameterValue(TEXT("BonePositionWS"), FLinearColor(BoneLocation));
        DynamicMaterial->SetScalarParameterValue(TEXT("MetallicRadius"), 20.0f);
    }
}

void AHDBBossCharacter::ApplyImpactDeform(const FVector& HitLocation, float Strength, FName HitBoneName)
{
    if (!DeformMaterial) return;

    FVector FinalImpactLocation = HitLocation;
    if (!HitBoneName.IsNone() && GetMesh())
    {
        FinalImpactLocation = GetMesh()->GetBoneLocation(HitBoneName);
    }

    ImpactLocation = FinalImpactLocation;
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

    if (DynamicMaterial && GetMesh())
    {
        FVector BoneLocation = GetMesh()->GetBoneLocation(TargetBoneName, EBoneSpaces::WorldSpace);
        DynamicMaterial->SetVectorParameterValue(TEXT("BonePositionWS"), FLinearColor(BoneLocation));
    }

}