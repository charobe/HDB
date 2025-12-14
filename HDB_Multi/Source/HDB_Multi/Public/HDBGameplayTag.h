// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace HDBGameplayTags
{
	//Input Tags
	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack);


	//Player Tag
	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light);
	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);

	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);



	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);

	//Enemy Tag
	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);

	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);	
	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);	


	//Shared Tag
	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);

	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);

	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeAttack);

	HDB_MULTI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Death);

}