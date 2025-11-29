#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnComponentBase.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HDB_MULTI_API UPawnComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	template <class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value,"T는 APawn을 상속해야 합니다.");
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value,"T는 AController를 상속해야 합니다.");
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};