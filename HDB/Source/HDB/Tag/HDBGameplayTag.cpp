#include "HDBGameplayTag.h"

namespace HDBGameplayTags
{
	// Input Tags
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipClawL, "InputTag.EquipClawL");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipClawR, "InputTag.EquipClawR");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipClawL, "InputTag.UnequipClawL");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipClawR, "InputTag.UnequipClawR");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ChangeFormWolf, "InputTag.ChangeFormWolf");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ChangeFormNormal, "InputTag.ChangeFormNormal");

	// Player Weapon Tag 

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_ClawL, "Player.Ability.Equip.ClawL");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_ClawR, "Player.Ability.Equip.ClawR");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_ClawL, "Player.Ability.Unequip.ClawL");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_ClawR, "Player.Ability.Unequip.ClawR");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_ClawL, "Player.Event.Equip.ClawL");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_ClawR, "Player.Event.Equip.ClawR");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_ClawL, "Player.Event.Unequip.ClawL");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_ClawR, "Player.Event.Unequip.ClawR");

	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_ClawL, "Player.Weapon.ClawL");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_ClawR, "Player.Weapon.ClawR");


	// Player Form Tag

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Form_Wolf, "Player.Ability.ChangeForm.Wolf");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Form_Normal, "Player.Ability.ChangeForm.Normal");

	UE_DEFINE_GAMEPLAY_TAG(Player_Form_Wolf, "Player.Form.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Player_Form_Normal, "Player.Form.Wolf");
}