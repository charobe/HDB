
#pragma once

#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

#define HDBTAG_ACTOR_ROTATE FGameplayTag::RequestGameplayTag(FName("Actor.Action.Rotate"))
#define HDBTAG_ACTOR_ISROTATING FGameplayTag::RequestGameplayTag(FName("Actor.State.IsRotating"))

namespace HDBGameplayTags
{
	// Input Tags
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump)

}

