
#pragma once

#include "NativeGameplayTags.h"

namespace HDBGameplayTags
{
	// Input Tags
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ChangeFormWolf);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ChangeFormNormal);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Claw);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Claw);

	// Player Weapon Tag 
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Claw);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Claw);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Claw);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Claw);

	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_ClawL);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_ClawR);


	// Player Form Tag

	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_ChangeForm_Wolf);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_ChangeForm_Normal);

	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Form_Wolf);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Form_Normal);

	// Player Attack Tag
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Claw);
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Claw);

	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);

	// Enemy Tag
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	// Shared Tag
	HDB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);




}

