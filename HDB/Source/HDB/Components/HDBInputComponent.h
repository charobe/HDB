// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "HDBInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class HDB_API UHDBInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
};

template<class UserObject, typename CallbackFunc>
inline void UHDBInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input Conpig Data Asset을 찾을 수 없습니다."));

	if (InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag);
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}
