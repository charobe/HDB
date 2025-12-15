// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EnemyUIComponent.h"
#include "Widget/HDBWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UHDBWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty())
	{
		return;
	}

	for (UHDBWidgetBase* DrawnWidget : EnemyDrawnWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}
}
