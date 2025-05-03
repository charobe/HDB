// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HDBWidgetBase.h"
#include "Interface/PawnUIInterface.h"


void UHDBWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitalized(PlayerUIComponent);
		}
	}


}

void UHDBWidgetBase::InitEnemyCratedWidget(AActor* OwningEnemyActor)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();

		checkf(EnemyUIComponent, TEXT("%s로부터 EnemyUIComponent를 추출하지 못했습니다."), *OwningEnemyActor->GetActorNameOrLabel());
	
		BP_OnOwningEnemyUIComponentInitalized(EnemyUIComponent);


	}
}
