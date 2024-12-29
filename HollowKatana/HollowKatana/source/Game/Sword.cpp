#include "Sword.h"
#include "Animation.h"
#include "ResourcesManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "../Parameter/GlobeGameParameters.h"
#include "Player.h"

Sword::Sword(Vector2 position, bool move_right) :ActorObject(position)
{
	set_render_layer(LAYER_ITEM_PLAYER + 1);
	set_collision_size({ 195,10 });
	set_collision_layer_self(CollisionLayer::EnemyProjectile);
	add_collision_layer(CollisionLayer::Player);
	//add_collision_layer(CollisionLayer::PlatformLarge);
	//add_collision_layer(CollisionLayer::PlatformSmall);

	Atlas* sword_atlas = ResourcesManager::GetInstance().find_atlas(move_right ? "atlas_Hornet_Sword_right" : "atlas_Hornet_Sword_left");
	animation = new Animation();
	animation->add_animation(sword_atlas);
	animation->set_loop(true);
	animation->set_interval(100);

	set_current_animation_reset(animation);
	this->velocity = { move_right ? this->speed : -this->speed, 0 };

}



Sword::~Sword()
{
	if(animation)
		delete animation;
}


void Sword::on_update(float delta)
{
	ActorObject::on_update(delta);

	Vector2 camera_position = SceneManager::GetInstance().get_main_camera()->get_position();
	Vector2 delta_position = this->get_current_posistion() - camera_position;

//	printf("Sword Position: %.2f\n", delta_position.x);

	if (delta_position.x  - this->get_collision_size().x > WIN_WIDTH ||
		delta_position.x + this->get_collision_size().x < 0)
	{
		is_clear = true;
		//printf("Sword out of screen\n");
	}

}


void Sword::handleCollision(const HitInfo& hit_info)
{
	ActorObject::handleCollision(hit_info);

	Player* player = dynamic_cast<Player*>(hit_info.actor);
	if (player && !player->is_rolling_now() && !player->is_invincible_now())
	{
		set_enable_collision(false);
		Pawn::DamageInfo damage_info;
		damage_info.damage = 18;
		damage_info.attacker = this;
		damage_info.invincible_time = 200.0f;
		player->on_hurt(damage_info);
	}
}