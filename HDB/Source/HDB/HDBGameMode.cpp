// Fill out your copyright notice in the Description page of Project Settings.


#include "HDBGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"


//void AHDBGameMode::Died(APlayerCharacter *DeadPlayer) {
//	PC->HandleDistruction();
//
//}

void AHDBGameMode::BeginPlay() {
	Super::BeginPlay();

	PC = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
}