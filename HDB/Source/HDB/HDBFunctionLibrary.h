// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Type/HDBEnumTypes.h"
#include "HDBFunctionLibrary.generated.h"

class UPlayerAbilitySystemComponent;
class UPawnCombatComponent;


/**
 * 
 */
UCLASS()
class HDB_API UHDBFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UPlayerAbilitySystemComponent* NativeGetASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "HDB|FunctionLibrary")
	static void AddGameplayTagToActor(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "HDB|FunctionLibrary")
	static void RemoveGameplayFromActor(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);
	
	UFUNCTION(BlueprintCallable, Category = "HDB|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EHDBConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "HDB|FunctionLibrary", meta = (DisplayName = "GetPawnCombatComponent", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EHDBValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "HDB|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

};