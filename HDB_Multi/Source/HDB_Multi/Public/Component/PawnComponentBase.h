// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HDB_MULTI_API UPawnComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
    template <class T>
    FORCEINLINE T* GetOwningPawn() const
    {
        static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T'는  APawn을 상속되야 합니다");
        return Cast<T>(GetOwner());
    }

    FORCEINLINE APawn* GetOwningPawn() const
    {
        return GetOwningPawn<APawn>();
    }

    template <class T>
    FORCEINLINE T* GetOwningController() const
    {
        static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T'는 AController에 상속되야 합니다");
        if (APawn* P = GetOwningPawn<APawn>())
        {
            return Cast<T>(P->GetController());
        }
        return nullptr;
    }

    FORCEINLINE AController* GetOwningController() const
    {
        return GetOwningController<AController>();
    }
		
};
