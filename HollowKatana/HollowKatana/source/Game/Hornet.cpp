#include "Hornet.h"
#include "StateMachine.h"
#include "ActorObject.h"
#include "RenderManager.h"
#include "AudioManager.h"
#include "PlayerEffect.h"
#include "ParticleManager.h"
#include "Animation.h"
#include "ActorManager.h"
#include "Vector2.h"
#include "ResourcesManager.h"
#include "TimerManager.h"
#include "HornetState.h"
#include "Player.h"
#include "Barb.h"
#include "Sword.h"
#include "SceneManager.h"
#include "HornetEffect.h"
#include "WidgetManager.h"
#include "WD_Hornet.h"
#include "ControllerManager.h"
#include "Controller.h"
#include "PlayerController.h"


Hornet::Hornet(Vector2 position) :Charactor(position)
{
	set_collision_size({ 60,140 });
	set_collision_layer_self(CollisionLayer::Eenemy);
	add_collision_layer(CollisionLayer::PlatformLarge);
	add_collision_layer(CollisionLayer::AirWall);

	set_render_layer(LAYER_ITEM_PLAYER - 2);

	//添加状态机
	if (state_machine)
	{
		//往状态机中注册对应状态状态
		state_machine->register_state("idle", new HornetIdleState());
		state_machine->register_state("run", new HornetRunState());
		state_machine->register_state("fall", new HornetFallState());
		state_machine->register_state("jump", new HornetJumpState());
		state_machine->register_state("aim", new HornetAimState());
		state_machine->register_state("squat", new HornetSquatState());
		state_machine->register_state("dash_in_air", new HornetDashInAirState());
		state_machine->register_state("hand_land", new HornetHandLandState());
		state_machine->register_state("dash_on_floor", new HornetDashOnGroundState());
		state_machine->register_state("throw_sword", new HornetThrowSwordState());
		state_machine->register_state("throw_silk", new HornetThrowSilkState());
		state_machine->register_state("throw_barb", new HornetThrowBarbState());
		state_machine->register_state("dead", new HornetDeadState());

		state_machine->set_entry("idle");
	}


	//添加向右攻击动画
	Atlas* atlas = ResourcesManager::GetInstance().find_atlas("atlas_Hornet_attack_silk_right");
	attack_effect_right = new Animation();
	attack_effect_right->add_animation(atlas);
	attack_effect_right->set_loop(false);
	attack_effect_right->set_interval(75);
	attack_effect_right->set_on_finished_callback([&] {
		attack_silk_box->set_visiable(false);
		});

	//添加向左攻击动画
	atlas = ResourcesManager::GetInstance().find_atlas("atlas_Hornet_attack_silk_left");
	attack_effect_left = new Animation();
	attack_effect_left->add_animation(atlas);
	attack_effect_left->set_loop(false);
	attack_effect_left->set_interval(75);
	attack_effect_left->set_on_finished_callback([&] {
		attack_silk_box->set_visiable(false);
		});

	//创建丝线攻击盒并设置默认动画
	attack_silk_box = ActorManager::GetInstance().create_actor<ActorObject>(Vector2(300, 300));
	attack_silk_box->set_enable_post_process(false);
	attack_silk_box->set_is_collision_trigger(true);
	attack_silk_box->set_render_layer(LAYER_ITEM_PARTICLE + 2);
	attack_silk_box->set_current_animation_reset(attack_effect_right);
	attack_silk_box->set_collision_size({ 230,230 });
	attack_silk_box->set_visiable(false);
	attack_silk_box->set_collision_layer_self(CollisionLayer::EnemyAttack);
	attack_silk_box->add_collision_layer(CollisionLayer::Player);
	attack_silk_box->set_hit_actor_callback([&](const HitInfo& hit_info) {
		attack_silk_box->set_enable_collision(false);
		Player* player = dynamic_cast<Player*>(hit_info.actor);;
		if (player && !player->is_invincible_now() && !player->is_rolling_now())
		{
			Pawn::DamageInfo damage_info;
			damage_info.damage = 10;
			damage_info.attacker = this;
			damage_info.invincible_time = 300.0f;
			player->on_hurt(damage_info);
		}
		});

	//创建冲刺攻击盒
	attack_dash_box = ActorManager::GetInstance().create_actor<ActorObject>(Vector2(300, 300));
	attack_dash_box->set_is_collision_trigger(true);
	attack_dash_box->set_collision_size({ 100,100 });
	attack_dash_box->set_visiable(false);
	attack_dash_box->set_collision_layer_self(CollisionLayer::EnemyAttack);
	attack_dash_box->add_collision_layer(CollisionLayer::Player);
	attack_dash_box->set_hit_actor_callback([&](const HitInfo& hit_info) {
		attack_dash_box->set_visiable(false);
		Player* player = dynamic_cast<Player*>(hit_info.actor);;
		if (player && !player->is_invincible_now() && !player->is_rolling_now())
		{
			Pawn::DamageInfo damage_info;
			switch (dash_type)
			{
			case Hornet::DashType::GROUND:
				damage_info.damage = 15;
				break;
			case Hornet::DashType::AIR:
				damage_info.damage = 20;
				break;
			default:
				damage_info.damage = 10;
				break;
			}
			damage_info.attacker = this;
			damage_info.invincible_time = 500.0f;
			player->on_hurt(damage_info);
		}
		});


	//无敌时间定时器
	timer_invincible.set_wait_time(invincible_time);
	timer_invincible.set_one_shot(true);
	timer_invincible.set_callback([&]() {
		is_invincible = false;
	//	printf("Hornet is invincible end\n");
		});


	sketch_image = new IMAGE();
	//剪影闪烁定时器
	timer_invulnerable_blink.set_wait_time(50);
	timer_invulnerable_blink.set_callback([&]() {
		is_showing_sketch_frame = !is_showing_sketch_frame;
		});

	wd_hornet = WidgetManager::GetInstance().createUserWidgetInstance<WD_Hornet>(nullptr, 1);
	PlayerController* player = ControllerManager::GetInstance().get_player(ControllerManager::PlayerType::Player_1);
	WidgetManager::GetInstance().addToView(wd_hornet, player);
}


Hornet::~Hornet()
{
	ActorManager::GetInstance().destory_actor(attack_silk_box);
	ActorManager::GetInstance().destory_actor(attack_dash_box);

	if (attack_effect_right)
		delete attack_effect_right;
	if (attack_effect_left)
		delete attack_effect_left;
	if (wd_hornet)
		WidgetManager::GetInstance().removeWidget(wd_hornet);

}


void Hornet::on_update(float delta)
{
	Charactor::on_update(delta);

	if (is_invincible)
	{
		timer_invulnerable_blink.on_update(delta);
		timer_invincible.on_update(delta);
	}
	else
		is_showing_sketch_frame = false;


	//若当前是白色剪影帧则执行
	if (is_showing_sketch_frame)
	{
		ImageInfo* image_info_temp = current_animation->get_current_frame_image_info();
		helper::sketch_image(image_info_temp->getImage(), sketch_image, { 255,255,255 });
		sketch_image_info.setBrightness(image_info_temp->getBrightness());
		sketch_image_info.setFrameNumber(image_info_temp->getFrameNumber());
		sketch_image_info.setImage(sketch_image, false);

		if (render_item)
			render_item->setImageInfo(&sketch_image_info, current_animation->get_current_frame_rect_src());
	}


	if(attack_silk_box)
		attack_silk_box->set_current_posistion({ position.x + attack_silk_pos_x_offset, position.y + attack_silk_pos_y_offset });

	if (attack_dash_box)
		attack_dash_box->set_current_posistion({ position.x + attack_dash_pos_x_offset, position.y + attack_dash_pos_y_offset });

	if (target)
	{
		is_face_rigth = (target->get_current_posistion().x - position.x) > 0;
		target_distance_x =abs(target->get_current_posistion().x - position.x);
	}

	if (wd_hornet)
	{
		float current_hp = hp / 100.0f;
		wd_hornet->setHP(current_hp);

	}

}

//受伤函数
void Hornet::on_hurt(DamageInfo damage_info)
{
	if(is_invincible) return;

	switch (rand() % 3)
	{
	case 0:
		AudioManager::GetInstance().PlaySoundAudio("res/audio/enemy/enemy_hurt_1.mp3", AudioManager::AudioType::Effect, 80);
		break;
	case 1:
		AudioManager::GetInstance().PlaySoundAudio("res/audio/enemy/enemy_hurt_2.mp3", AudioManager::AudioType::Effect, 80);
		break;
	case 2:
		AudioManager::GetInstance().PlaySoundAudio("res/audio/enemy/enemy_hurt_3.mp3", AudioManager::AudioType::Effect, 80);
		break;
	default:
		break;
	}
	is_invincible = true;
	timer_invincible.set_wait_time(damage_info.invincible_time);
	timer_invincible.restart();
	hp -= damage_info.damage;
	if (hp <= 0)
	{
		hp = 0;
	}
		
}

//生成刺球
void Hornet::generate_barbs()
{
	int num_new_barbs = rand() % 4 + 3;					//生成3-6个新弹丸
	if (barb_num >= MAX_BARB_NUM) num_new_barbs = 1;	//如果已经满了，则只生成1个
	//printf("num_new_barbs:%d\n", num_new_barbs);
	Vector2 camera_pos = SceneManager::GetInstance().get_main_camera()->get_position();

	int width_grid = getwidth() / num_new_barbs;
	for (int i = 0; i < num_new_barbs; i++)
	{
		int rand_x = rand() % ( width_grid) + width_grid * i + camera_pos.x;
		int rand_y = rand() % 251 + 200 + camera_pos.x;
		Vector2 bast_pos = get_current_posistion();
		float pos_x_offset = is_face_rigth ? 35 : -25;
		Barb *barb = ActorManager::GetInstance().create_actor<Barb>(Vector2(bast_pos.x + pos_x_offset, bast_pos.y - 50));
		barb->set_move_target(Vector2(rand_x, rand_y));
		barb->set_hit_callback([&]() {
			barb_num--;
		//	printf("barb_num:%d\n", barb_num);
			});
	}
	barb_num += num_new_barbs;
	//printf("total barb_num:%d\n", barb_num);
	AudioManager::GetInstance().PlaySoundAudio("res/audio/enemy/enemy_throw_barbs.mp3", AudioManager::AudioType::Effect, 80);

}

//投掷剑
void Hornet::throw_sword()
{
	ActorManager::GetInstance().create_actor<Sword>(Vector2(this->get_current_posistion().x, 
		this->get_current_posistion().y - this->get_collision_size().y / 2 + 20),
		this->get_is_face_rigth());
	AudioManager::GetInstance().PlaySoundAudio("res/audio/enemy/enemy_throw_sword.mp3", AudioManager::AudioType::Effect, 80);
}

//丝线攻击
void Hornet::attack_silk()
{
	set_velocity_x(0);
	if(!attack_silk_box) return;
	attack_silk_box->set_visiable(true);
	attack_silk_box->set_current_animation_reset(get_is_face_rigth() ? attack_effect_right : attack_effect_left);
	AudioManager::GetInstance().PlaySoundAudio("res/audio/enemy/enemy_throw_silk.mp3", AudioManager::AudioType::Effect, 80);
}

//冲刺攻击开始
void Hornet::attack_dash_start(DashType dash_type)
{
	if (is_dashing) return;
	switch (dash_type)
	{
	case Hornet::DashType::GROUND:
	{
		attack_dash_box->set_visiable(true);
		velocity.x = is_face_rigth ? DASH_SPEED_GROUND : -DASH_SPEED_GROUND;
		is_dashing = true;
		attack_dash_box->set_collision_size({ 100,50 });
		attack_dash_pos_x_offset = is_face_rigth ?  35 : -25;
		attack_dash_pos_y_offset = -30.0f;
		AudioManager::GetInstance().PlaySoundAudio("res/audio/enemy/enemy_dash.mp3", AudioManager::AudioType::Effect, 80);
		this->dash_type = dash_type;
		Vector2 effect_pos;
		if (get_is_face_rigth())
			effect_pos = { get_current_posistion().x - 600,get_current_posistion().y - 250 };
		else
			effect_pos = { get_current_posistion().x - 550,get_current_posistion().y - 250 };

		ParticleManager::getInstance().createParticleInstance<DashOnFloorEffect>(effect_pos, get_is_face_rigth(),75);

		break;
	}
	case Hornet::DashType::AIR:
	{
		if (!on_ground)
		{
			is_dashing = true;
			attack_dash_box->set_visiable(true);
			set_floating(true);
			if (target)
			{
				target_pos = target->get_current_posistion();
				this->velocity = (target_pos - get_current_posistion()).normalize() * DASH_SPEED_AIR;
			}
			attack_dash_box->set_collision_size({ 80,80 });
			attack_dash_pos_x_offset = is_face_rigth ? 25 : -25;
			attack_dash_pos_y_offset = -45.0f;
			AudioManager::GetInstance().PlaySoundAudio("res/audio/enemy/enemy_dash.mp3", AudioManager::AudioType::Effect, 80);
			this->dash_type = dash_type;
			Vector2 effect_pos;
			if (get_is_face_rigth())
				effect_pos = { get_current_posistion().x - 330,get_current_posistion().y - 360 };
			else
				effect_pos = { get_current_posistion().x - 330,get_current_posistion().y - 360 };

			ParticleManager::getInstance().createParticleInstance<DashInAirEffect>(effect_pos, get_is_face_rigth(), 75);

		}
		break;
	}
	default:
		break;
	}


}

//冲刺攻击结束
void Hornet::attack_dash_end(DashType dash_type)
{
	attack_dash_box->set_visiable(false);
	switch (dash_type)
	{
	case Hornet::DashType::GROUND:
	{
		set_velocity_x(0);
		break;
	}
	case Hornet::DashType::AIR:
	{
		set_velocity(0,0);
		set_floating(false);
		break;
	}
	default:
		break;
	}
	is_dashing = false;
}

//处理碰撞
void Hornet::handleCollision(const HitInfo& hit_info)
{
	Charactor::handleCollision(hit_info);

	if (get_floating())
	{
		attack_dash_end(DashType::AIR);
	}
}

//重写on_land函数，播放音效和特效
void Hornet::on_land()
{
	//播放音效和特效
	
}


