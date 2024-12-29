#include "PlayerEffect.h"
#include "ResourcesManager.h"
#include "ImageInfo.h"

JumpEffect::JumpEffect(Vector2 position, int lifespan) : Particle(position, lifespan)
{
	ImageInfo* effect_jump = ResourcesManager::GetInstance().find_image("img_player_jump_vfx");
	set_image_info(effect_jump);
}


LandEffect::LandEffect(Vector2 position, int lifespan) : Particle(position, lifespan)
{
	ImageInfo* effect_land = ResourcesManager::GetInstance().find_image("img_player_land_vfx");
	set_image_info(effect_land);
}


AttackEffect::AttackEffect(Vector2 position, int lifespan, AttackDirection direction): Particle(position, lifespan)
{
	ImageInfo* effect_attack = nullptr;
	switch (direction)
	{
	case AttackEffect::LEFT:
		effect_attack = ResourcesManager::GetInstance().find_image("img_player_attack_left_vfx");
		break;
	case AttackEffect::RIGHT:
		effect_attack = ResourcesManager::GetInstance().find_image("img_player_attack_right_vfx");
		break;
	case AttackEffect::UP:
		effect_attack = ResourcesManager::GetInstance().find_image("img_player_attack_up_vfx");
		break;
	case AttackEffect::DOWN:
		effect_attack = ResourcesManager::GetInstance().find_image("img_player_attack_down_vfx");
		break;
	default:
		break;
	}
	set_image_info(effect_attack);
}

