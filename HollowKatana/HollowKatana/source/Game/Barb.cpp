#include "Barb.h"
#include "Animation.h"
#include "ResourcesManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "../Parameter/GlobeGameParameters.h"
#include "PlayerController.h"
#include "ControllerManager.h"
#include "AudioManager.h"
#include "Player.h"

Barb::Barb(Vector2 position) : ActorObject(position)
{
	this->base_position = position;

	set_render_layer(LAYER_ITEM_PLAYER + 1);
	set_collision_size({ 20,20 });
	set_collision_layer_self(CollisionLayer::EnemyProjectile);
	add_collision_layer(CollisionLayer::Player);
	add_collision_layer(CollisionLayer::PlatformLarge);
	add_collision_layer(CollisionLayer::PlatformSmall);
	add_collision_layer(CollisionLayer::PlayerAttack);

	Atlas* barb_loose_atlas = ResourcesManager::GetInstance().find_atlas("atlas_Hornet_barb_loose");
	Atlas* barb_break_atlas = ResourcesManager::GetInstance().find_atlas("atlas_Hornet_barb_break");
	
	animation_loose = new Animation();
	animation_loose->add_animation(barb_loose_atlas);
	animation_loose->set_loop(true);
	animation_loose->set_interval(150);

	animation_break = new Animation();
	animation_break->add_animation(barb_break_atlas);
	animation_break->set_loop(false);
	animation_break->set_interval(65);
	animation_break->set_on_finished_callback([&]() { 
		if (hit_callback)
			hit_callback();
		is_clear = true;
		});

	set_current_animation_reset(animation_loose);

	timer_idle.set_wait_time((float)(rand() % 7000 + 3000));  //设置随机等待时间,范围3000-10000ms
	timer_idle.set_one_shot(true);
	timer_idle.set_callback([&]() {
		if (current_stage == Stage::Idle)
		{
			current_stage = Stage::Aim;
			base_position = get_current_posistion();
		}
		});


	timer_aim.set_wait_time(750);
	timer_aim.set_one_shot(true);
	timer_aim.set_callback([&]() {
		if (current_stage == Stage::Aim)
		{
			current_stage = Stage::Dash;
			PlayerController* player = ControllerManager::GetInstance().get_player(ControllerManager::PlayerType::Player_1);
			if (player->get_owned_character())
			{
				target_position = player->get_owned_character()->get_current_posistion();
				target_position.y -= (player->get_owned_character()->get_collision_size().y / 2 - 10);
			}
			else
			{
				Vector2 camera_position = SceneManager::GetInstance().get_main_camera()->get_position();
				target_position = { camera_position.x + WIN_WIDTH, camera_position.y + WIN_HEIGHT};
			}
			this->velocity = (target_position - base_position).normalize() * SPEED_DASH;
		}
		});


}


Barb::~Barb()
{
	if (animation_loose)
		delete animation_loose;
	if (animation_break)
		delete animation_break;
	//printf("Barb Destructor\n");
}


void Barb::on_update(float delta)
{
	ActorObject::on_update(delta);

	//更新定时器
	if(current_stage == Stage::Idle)
		timer_idle.on_update(delta);
	if(current_stage == Stage::Aim)
		timer_aim.on_update(delta);

	
	switch (current_stage)
	{
	case Stage::Move:
		{
			if (last_length - (target_position - get_current_posistion()).length() < 0.0f)
			{
				base_position = get_current_posistion();
				current_stage = Stage::Idle;
				velocity = Vector2(0, 0);
			}
			last_length = (target_position - get_current_posistion()).length();
			break;
		}
	case Stage::Idle:
		{
			if (rand_distant < 0)
				rand_distant = rand() % 2;    //设置随机方向

			//更新移动逻辑
			total_delta_time += delta;
			float offset_y = sin(total_delta_time / 300) * 30;
			set_current_posistion({ base_position.x,rand_distant ? base_position.y + offset_y : base_position.y - offset_y });
			break;
		}
	case Stage::Aim:
		{
			float x_diff = rand() % 1 ? rand() % 15 : -rand() % 15;
			set_current_posistion({ base_position.x + x_diff, get_current_posistion().y });
			break;
		}
	case Stage::Dash:
		{
			Vector2 camera_position = SceneManager::GetInstance().get_main_camera()->get_position();
			Vector2 delta_position = this->get_current_posistion() - camera_position;

			if (delta_position.x - this->get_collision_size().x > WIN_WIDTH ||
				delta_position.x + this->get_collision_size().x < 0)
			{
				this->velocity = Vector2(0, 0);
				if (hit_callback)
					hit_callback();
				is_clear = true;
				//printf("Sword out of screen\n");
			}
			break;
		}
	default:
		break;
	}



}

void Barb::handleCollision(const HitInfo& hit_info)
{
	ActorObject::handleCollision(hit_info);

	Player* player = dynamic_cast<Player*>(hit_info.actor);
	if (player)
	{
		if (!player->is_rolling_now() && !player->is_invincible_now())
		{
			set_enable_collision(false);
			on_break();
			Pawn::DamageInfo damage_info;
			damage_info.damage = 3;
			damage_info.attacker = this;
			damage_info.invincible_time = 150.0f;
			player->on_hurt(damage_info);
		}
	}
	else
	{
		set_enable_collision(false);
		on_break();
	}
	
}

void Barb::on_break()
{
	AudioManager::GetInstance().PlaySoundAudio("res/audio/enemy/barb_break.mp3", AudioManager::AudioType::Effect, 80);
	set_current_animation_reset(animation_break);
	this->velocity = Vector2(0, 0);
}


void Barb::set_move_target(Vector2 target)
{
	target_position = target;
	current_stage = Stage::Move;
	timer_idle.restart();
	timer_aim.restart();
	this->velocity = (target_position - get_current_posistion()).normalize() * SPEED_DASH;
	last_length = (target_position - get_current_posistion()).length();
	total_delta_time = 0;
}

