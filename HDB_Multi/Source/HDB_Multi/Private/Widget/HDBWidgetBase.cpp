// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HDBWidgetBase.h"
#include "Interface/PawnUIInterface.h"

void UHDBWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	APawn* OwningPawn = GetOwningPlayerPawn();
	if (!OwningPawn)
	{
		return;
	}

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningPawn))
	{
		if (UPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningHeroUIComponentInitialized(PlayerUIComponent);
		}
	}
}

void UHDBWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (!OwningEnemyActor)
	{
		return;
	}

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();
		if (!EnemyUIComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("EnemyUIComponent is null on %s"),
				*OwningEnemyActor->GetActorNameOrLabel());
			return;
		}

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
