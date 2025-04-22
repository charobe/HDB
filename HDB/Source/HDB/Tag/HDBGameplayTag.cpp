#include "HDBGameplayTag.h"

namespace HDBGameplayTags
{
	// Input Tags
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ChangeFormWolf, "InputTag.ChangeFormWolf");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ChangeFormNormal, "InputTag.ChangeFormNormal");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Claw, "InputTag.LightAttack.Claw");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Claw, "InputTag.HeavyAttack.Claw");



	// Player Weapon Tag 

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Claw, "Player.Ability.Equip.Claw");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Claw, "Player.Ability.Unequip.Claw");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Claw, "Player.Event.Equip.Claw");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_ClawL, "Player.Event.Unequip.Claw");

	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_ClawL, "Player.Weapon.ClawL");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_ClawR, "Player.Weapon.ClawR");


	// Player Form Tag

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Form_Wolf, "Player.Ability.ChangeForm.Wolf");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Form_Normal, "Player.Ability.ChangeForm.Normal");

	UE_DEFINE_GAMEPLAY_TAG(Player_Form_Wolf, "Player.Form.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Player_Form_Normal, "Player.Form.Wolf");


	// Player Attack Tag

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Claw, "Player.Ability.Attack.Light.Claw");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Claw, "Player.Ability.Attack.Heavy.Claw");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher");

}