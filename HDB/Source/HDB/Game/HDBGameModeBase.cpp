// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HDBGameModeBase.h"
#include "HDBGameStateBase.h"
#include "Player/HDBPlayerController.h"


AHDBGameModeBase::AHDBGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/HDB/Character/Player/BP_HDBCharacterPlayer.BP_HDBCharacterPlayer_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/HDB.HDBPlayerController"));

	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
	PlayerControllerClass = AHDBPlayerController::StaticClass();

	GameStateClass = AHDBGameStateBase::StaticClass();
}

void AHDBGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void AHDBGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueID, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueID, ErrorMessage);
}

APlayerController* AHDBGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* NewPlayerController = Super::Login(NewPlayer,InRemoteRole,Portal,Options,UniqueId,ErrorMessage);

	return NewPlayerController;
}

void AHDBGameModeBase::PostLogin(APlayerController* NewPlayer)
{

	Super::PostLogin(NewPlayer);
}

void AHDBGameModeBase::StartPlay()
{
	Super::StartPlay();
}
