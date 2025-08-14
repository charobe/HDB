 // Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HDBGameInstance.h"
#include "GameFramework/GameUserSettings.h"


void UHDBGameInstance::Init()
{
    Super::Init();

    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (Settings)
    {
        Settings->SetScreenResolution(FIntPoint(1920, 1080)); 
        Settings->SetFullscreenMode(EWindowMode::Windowed);
        Settings->ApplySettings(true); // true = save to ini
    }
}
