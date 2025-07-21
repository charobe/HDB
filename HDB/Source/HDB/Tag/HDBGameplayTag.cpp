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
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dash, "InputTag.Dash");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SwitchTarget, "InputTag.SwitchTarget");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld_Block, "InputTag.MustBeHeld.Block");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle, "InputTag.Toggle");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle_TargetLock, "InputTag.Toggle.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Get_Item, "InputTag.Get.Item");


	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Claw, "Player.Ability.Equip.Claw");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Claw, "Player.Ability.Unequip.Claw");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Claw, "Player.Ability.Attack.Light.Claw");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Claw, "Player.Ability.Attack.Heavy.Claw");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Form_Wolf, "Player.Ability.ChangeForm.Wolf");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Form_Normal, "Player.Ability.ChangeForm.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dash, "Player.Ability.Dash");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block, "Player.Ability.Block");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_TargetLock, "Player.Ability.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Get_Potion, "Player.Ability.Get.Potion");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Claw, "Player.Event.Equip.Claw");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_ClawL, "Player.Event.Unequip.Claw");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SuccessfulBlock, "Player.Event.SuccessfulBlock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Left, "Player.Event.SwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Right, "Player.Event.SwitchTarget.Right");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UseItem, "Player.Event.UseItem");

	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_ClawL, "Player.Weapon.ClawL");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_ClawR, "Player.Weapon.ClawR");

	UE_DEFINE_GAMEPLAY_TAG(Player_Form_Wolf, "Player.Form.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Player_Form_Normal, "Player.Form.Wolf");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Dash, "Player.Status.Dash");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Block, "Player.Status.Block");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_TargetLock, "Player.Status.TargetLock");


	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType_Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType_Heavy");

	// Enemy Tag
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_DropPotion, "Enemy.Ability.DropPotion");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Unblockable, "Enemy.Status.Unblockable");


	// Shared Tag
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");


}