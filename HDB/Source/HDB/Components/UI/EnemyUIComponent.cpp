// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/EnemyUIComponent.h"
#include "Widget/HDBWidgetBase.h"

void UEnemyUIComponent::RegisterWidget(UHDBWidgetBase* InWidget)
{
	DrawnWidgets.Add(InWidget);
}

void UEnemyUIComponent::RemoveWidget()
{
	if (DrawnWidgets.IsEmpty()) 
	{
		return;
	}

	for (UHDBWidgetBase* Widget : DrawnWidgets)
	{
		if (Widget)
		{
			Widget->RemoveFromParent();
		}
	}
}