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

    if (ClawMarkDecalMaterial)
    {
        FVector Location = GetActorLocation() + DecalLocationOffset;
        FRotator Rotation = DecalRotationOffset;
        FVector DecalSize = FVector(60.0f, 60.0f, 60.0f);

        // FVector ScratchLocation = Hit.ImpactPoint;
        FVector BossCenter = GetActorLocation();
        FVector DirectionToCenter = BossCenter - Location;
        FRotator DecalRotation = DirectionToCenter.Rotation();

        //ScratchMesh->SetWorldRotation((BossCenter - Hit.ImpactPoint).Rotation());
        /*
        FVector ImpactLocation = Hit.ImpactPoint;
        FVector Normal = Hit.ImpactNormal;
        FVector SpawnOffset = Normal * 0.2f;

        ScratchMesh->SetWorldLocation(ImpactLocation + SpawnOffset);
        */

        UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(
            GetWorld(),
            ClawMarkDecalMaterial,
            DecalSize,
            Location,
            DecalRotation,
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