// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HDBBossCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

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


    if (ClawMarkDecalMaterial)
    {
        FVector Location = GetActorLocation() + DecalOffset;
        FRotator Rotation = FRotator(0, 0, 0);
        FVector DecalSize = FVector(60.0f, 60.0f, 60.0f);

        UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(
            GetWorld(),
            ClawMarkDecalMaterial,
            DecalSize,
            Location,
            Rotation,
            5.0f
        );

        if (Decal)
        {
            Decal->SetFadeScreenSize(0.01f);
        }

        FVector DecLocation = GetActorLocation() + FVector(0, 0, 100);

        DrawDebugSphere(GetWorld(), Location, 10.0f, 12, FColor::Red, false, 5.0f);

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