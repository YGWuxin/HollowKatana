#include "Player.h"
#include "StateMachine.h"
#include "ActorObject.h"
#include "RenderManager.h"
#include "PlayerState.h"
#include "AudioManager.h"
#include "PlayerEffect.h"
#include "ParticleManager.h"
#include "Animation.h"
#include "ActorManager.h"
#include "Vector2.h"
#include "ResourcesManager.h"
#include "TimerManager.h"
#include "Hornet.h"
#include "WidgetManager.h"
#include "WD_Player.h"
#include "SceneManager.h"

Player::Player(Vector2 position) :Charactor(position)
{
	set_collision_size({ 60,80 });
	set_collision_layer_self(CollisionLayer::Player);
	add_collision_layer(CollisionLayer::PlatformLarge);
	add_collision_layer(CollisionLayer::AirWall);

	sketch_image = new IMAGE();
	sketch_image_info.setImage(sketch_image);

	//添加状态机
	if (state_machine)
	{
		//往状态机中注册对应状态状态
		state_machine->register_state("idle", new PlayerIdleState());
		state_machine->register_state("run", new PlayerRunState());
		state_machine->register_state("jump", new PlayerJumpState);
		state_machine->register_state("fall", new PlayerFallState);
		state_machine->register_state("roll", new PlayerRollState);
		state_machine->register_state("attack", new PlayerAttackState());
		state_machine->register_state("dead", new PlayerDeadState());
		state_machine->set_entry("idle");
		//current_movement_state = MovementState::Idle;
	}

	set_enable_post_process(false);

	timer_roll.set_one_shot(true);
	timer_roll.set_wait_time(roll_time);
	timer_roll.set_callback([&] {
		is_rolling = false;
		is_move_lock = false;
		velocity.x = 0;
		});

	//添加向右攻击动画
	ImageInfo* info = ResourcesManager::GetInstance().find_image("img_player_attack_right_vfx");
	attack_effect_right = new Animation();
	attack_effect_right->add_animation(info);
	attack_effect_right->set_loop(false);
	attack_effect_right->set_interval(50);
	attack_effect_right->set_on_finished_callback([&] {
		attack_box->set_visiable(false);
		});

	//添加向左攻击动画
	info = ResourcesManager::GetInstance().find_image("img_player_attack_left_vfx");
	attack_effect_left = new Animation();
	attack_effect_left->add_animation(info);
	attack_effect_left->set_loop(false);
	attack_effect_left->set_interval(50);
	attack_effect_left->set_on_finished_callback([&] {
		attack_box->set_visiable(false);
		});

	//添加向上攻击动画
	info = ResourcesManager::GetInstance().find_image("img_player_attack_up_vfx");
	attack_effect_up = new Animation();
	attack_effect_up->add_animation(info);
	attack_effect_up->set_loop(false);
	attack_effect_up->set_interval(50);
	attack_effect_up->set_on_finished_callback([&] {
		attack_box->set_visiable(false);
		});

	//添加向下攻击动画
	info = ResourcesManager::GetInstance().find_image("img_player_attack_down_vfx");
	attack_effect_down = new Animation();
	attack_effect_down->add_animation(info);
	attack_effect_down->set_loop(false);
	attack_effect_down->set_interval(50);
	attack_effect_down->set_on_finished_callback([&] {
		attack_box->set_visiable(false);
		});

	//创建攻击盒并设置默认动画
	attack_box = ActorManager::GetInstance().create_actor<ActorObject>(Vector2(300,400));
	attack_box->set_enable_post_process(false);
	attack_box->set_is_collision_trigger(true);
	attack_box->set_render_layer(LAYER_ITEM_PARTICLE);
	attack_box->set_current_animation_reset(attack_effect_right);
	attack_box->set_collision_size({ 285,100 });
	attack_box->set_visiable(false);
	attack_box->set_collision_layer_self(CollisionLayer::PlayerAttack);
	attack_box->add_collision_layer(CollisionLayer::Eenemy);
	attack_box->set_hit_actor_callback([&](const HitInfo& hit_info) {
		attack_box->set_enable_collision(false);
		Charactor* enemy = dynamic_cast<Hornet*>(hit_info.actor);;
		if (enemy)
		{
			Pawn::DamageInfo damage_info;
			Camera* camera = SceneManager::GetInstance().get_main_camera();
			damage_info.damage = 3;
			int rand_num = rand() % 101;  // 0-100
			strenth = 2.0f;
			duration = 150.0f;
			if (rand_num <= 2)
			{
				damage_info.damage = 12;
				strenth = 8.0f;
				duration = 200.0f;
			}
			else if (rand_num <= 12)
			{
				damage_info.damage = 6;
				strenth = 4.0f;
				duration = 200.0f;
			}
			player_mp += 10.0f;
			if(player_mp >= 100.0f)
				player_mp = 100.0f;

			camera->Shake(strenth, duration,4);
			damage_info.attacker = this;
			damage_info.invincible_time = 400.0f;
			enemy->on_hurt(damage_info);
		}
		});

	//无敌时间定时器
	timer_invincible.set_wait_time(invincible_time);
	timer_invincible.set_one_shot(true);
	timer_invincible.set_callback([&]() {
		is_invincible = false;
		});


	//剪影闪烁定时器
	timer_invulnerable_blink.set_wait_time(50);
	timer_invulnerable_blink.set_callback([&]() {
		is_showing_sketch_frame = !is_showing_sketch_frame;
		});

	wd_player = WidgetManager::GetInstance().createUserWidgetInstance<WD_Player>(nullptr, 1);
	

	timer_player_stamina_start.set_wait_time(PLAYER_STAMINA_RESTORE_TIME);
	timer_player_stamina_start.set_one_shot(true);
	timer_player_stamina_start.set_callback([&]() {
		is_player_stamina_start = true;
		});


	timer_bullet_time.set_wait_time(PLAYER_MP_RESTORE_TIME);
	timer_bullet_time.set_one_shot(true);
	timer_bullet_time.set_callback([&]() {
		is_player_mp_start = true;
		player_mp_taget = 100.0f;
		});

}


Player::~Player()
{
	ActorManager::GetInstance().destory_actor(attack_box);
	if(attack_effect_right)
		delete attack_effect_right;
	if(attack_effect_left)
		delete attack_effect_left;
	if(attack_effect_up)
		delete attack_effect_up;
	if(attack_effect_down)
		delete attack_effect_down;
	if (wd_player)
		WidgetManager::GetInstance().removeWidget(wd_player);

	//printf("Player Destory\n");
}



void Player::on_update(float delta)
{
	Charactor::on_update(delta);

	timer_roll.on_update(delta);
	
	timer_player_stamina_start.on_update(TimerManager::GetInstance().get_real_time());

	timer_bullet_time.on_update(TimerManager::GetInstance().get_real_time());

	timer_invincible.on_update(delta);
	if (is_invincible)
	{
		timer_invulnerable_blink.on_update(delta);
	//	printf("Player is invulnerable\n");
	}
	else
		is_showing_sketch_frame = false;

	if (player_hp > 0)
	{
		if (is_player_stamina_start)
		{
			TimerManager::GetInstance().lerp_float(player_stamina, player_stamina_start, 100.0f, PLAYER_STAMINA_RESTORE_SPEED, TimerManager::TimerType::RealTime);
		}

		if (player_mp_taget == 100.0f && is_player_mp_start)
			TimerManager::GetInstance().lerp_float(player_mp, player_mp_start, player_mp_taget, PLAYER_MP_RESTORE_SPEED, TimerManager::TimerType::RealTime);
		else if (player_mp_taget == 0.0f && !is_player_mp_start)
			TimerManager::GetInstance().lerp_float(player_mp, player_mp_start, player_mp_taget, PLAYER_MP_REDUCE_SPEED, TimerManager::TimerType::RealTime);

		if (player_mp == 0.0f && player_mp_taget == 0.0f)
			move_on_bullet_time_end();


		TimerManager::GetInstance().lerp_float(current_bullet_time, taget_bullet_time, speed_factor, TimerManager::TimerType::RealTime);
		TimerManager::GetInstance().lerp_float(current_brighness, taget_brighness, speed_factor, TimerManager::TimerType::RealTime);

	}
	else
	{
		player_stamina = 0.0f;
		player_mp = 0.0f;
		current_bullet_time = 1.0f;
		current_brighness = 1.0f;
	}
	

	//若当前是白色剪影帧则执行
	if (is_showing_sketch_frame && is_enable_sketch)
	{
		ImageInfo* image_info_temp = current_animation->get_current_frame_image_info();
		helper::sketch_image(image_info_temp->getImage(), sketch_image, {255,0,0});
		sketch_image_info.setBrightness(image_info_temp->getBrightness());
		sketch_image_info.setFrameNumber(image_info_temp->getFrameNumber());
		sketch_image_info.setImage(sketch_image,false);

		if (render_item)
			render_item->setImageInfo(&sketch_image_info,current_animation->get_current_frame_rect_src());
	}


	attack_box->set_current_posistion({ position.x + attack_box_pos_x_offset, position.y + attack_box_pos_y_offset });

	
	

	if (is_bullet_time)
	{
		TimerManager::GetInstance().set_time_dilation(current_bullet_time);
		RenderManager::getInstance().setAllItemsBrightness(current_brighness);
	}
	if (current_bullet_time >= 1.0f)
	{
		is_bullet_time = false;
	}
	

	if (wd_player)
	{
		float current_hp = player_hp / 100.0f;
		wd_player->setHP(current_hp);

		float current_stamina = player_stamina / 100.0f;
		wd_player->setStamina(current_stamina);

		float current_mp = player_mp / 100.0f;
		wd_player->setMP(current_mp);

	}

}



void Player::init_input_event()
{
	Charactor::init_input_event();
	//添加输入事件
	addInputEvent("move_right", bind(&Player::move_right_down, this), KeyState::KEY_DOWN);
	addInputEvent("move_right", bind(&Player::move_right_up, this), KeyState::KEY_UP);

	addInputEvent("move_left", bind(&Player::move_left_down, this), KeyState::KEY_DOWN);
	addInputEvent("move_left", bind(&Player::move_left_up, this), KeyState::KEY_UP);

	addInputEvent("jump", bind(&Player::move_on_jump_down, this), KeyState::KEY_DOWN);
	addInputEvent("jump", bind(&Player::move_on_jump_up, this), KeyState::KEY_UP);

	addInputEvent("crouch", bind(&Player::move_on_crouch_down, this), KeyState::KEY_DOWN);
	addInputEvent("crouch", bind(&Player::move_on_crouch_up, this), KeyState::KEY_UP);

	addInputEvent("roll", bind(&Player::move_roll_down, this), KeyState::KEY_DOWN);
	addInputEvent("roll", bind(&Player::move_roll_up, this), KeyState::KEY_UP);

	addInputEvent("attack", bind(&Player::move_on_attack, this), KeyState::KEY_DOWN);

	addInputEvent("bullet_time", bind(&Player::move_on_bullet_time_start, this), KeyState::KEY_DOWN);
	addInputEvent("bullet_time", bind(&Player::move_on_bullet_time_end, this), KeyState::KEY_UP);
}


void Player::move_right_down()
{
	Move_right_start();
}

void Player::move_right_up()
{
	Move_right_stop();
}

void Player::move_left_down()
{
	Move_left_start();
}

void Player::move_left_up()
{
	Move_left_stop();
}


void Player::move_on_jump_down()
{
	is_up_key_pressed = true;
	if (is_rolling || is_move_lock || velocity.y != 0) return;
	if (!reduce_stamina(PLAYER_JUMP_STAMINA)) return;
	Move_jump();
	//播放音效和特效
	AudioManager::GetInstance().PlaySoundAudio("res/audio/player/player_jump.mp3", AudioManager::AudioType::Effect, 50);
	Vector2 effect_pos = { get_collision_position().x - 75, get_collision_position().y - 132 };
	ParticleManager::getInstance().createParticleInstance<JumpEffect>(effect_pos, 50);
}

void Player::move_on_jump_up()
{
	is_up_key_pressed = false;
	
}

void Player::move_on_crouch_down()
{
	is_down_key_pressed = true;
}

void Player::move_on_crouch_up()
{
	is_down_key_pressed = false;
}


void Player::move_roll_down()
{
	if (is_rolling || !on_ground || is_attacking || is_key_rolling_dowm || is_move_lock)
		return;
	if (!reduce_stamina(PLAYER_ROLL_STAMINA)) return;
	is_rolling = true;
	is_move_lock = true;
	timer_roll.restart();
	velocity.x = is_face_rigth ? roll_speed : -roll_speed;
	is_key_rolling_dowm = true;
}

void Player::move_roll_up()
{
	is_key_rolling_dowm = false;
}



void Player::move_on_attack()
{
	if (is_rolling || is_attacking)
		return;
	if (!reduce_stamina(PLAYER_ATTACK_STAMINA)) return;
	is_attacking = true;
	//播放音效和特效
	switch (rand() % 3)
	{
	case 0:
		AudioManager::GetInstance().PlaySoundAudio("res/audio/player/player_attack_1.mp3", AudioManager::AudioType::Effect, 50);
		break;
	case 1:
		AudioManager::GetInstance().PlaySoundAudio("res/audio/player/player_attack_2.mp3", AudioManager::AudioType::Effect, 50);
		break;
	case 2:
		AudioManager::GetInstance().PlaySoundAudio("res/audio/player/player_attack_3.mp3", AudioManager::AudioType::Effect, 50);
	default:
		break;
	}

	if (is_face_rigth)
	{
		attack_box->set_current_animation_reset(attack_effect_right);
		attack_box_pos_x_offset = 30.0f;
		attack_box_pos_y_offset = -50.0f;
		attack_box->set_render_item_offset(0, -20);
		attack_box->set_collision_size({ 285,90 });
	}
	else
	{
		attack_box->set_current_animation_reset(attack_effect_left);
		attack_box_pos_x_offset = -30.0f;
		attack_box_pos_y_offset = -50.0f;
		attack_box->set_render_item_offset(0, -20);
		attack_box->set_collision_size({ 285,90 });
	}

	if (is_down_key_pressed)
	{
		attack_box->set_current_animation_reset(attack_effect_down);
		attack_box_pos_x_offset = 0.0f;
		attack_box_pos_y_offset = 0.0f;
		attack_box->set_render_item_offset(0, -20);
		attack_box->set_collision_size({ 110,285 });
	}

	if (is_up_key_pressed)
	{
		attack_box->set_current_animation_reset(attack_effect_up);
		attack_box_pos_x_offset = 0.0f;
		attack_box_pos_y_offset = -80.0f;
		attack_box->set_render_item_offset(0, 0);
		attack_box->set_collision_size({ 110,285 });
	}

	attack_box->set_visiable(true);

}

void Player::move_on_bullet_time_start()
{
	if(is_bullet_time_enable || player_mp <= 0.0f) return;
	AudioManager::GetInstance().PlaySoundAudio("res/audio/player/bullet_time.mp3", AudioManager::AudioType::Effect,150);
	taget_bullet_time = 0.3f;
	taget_brighness = 0.4f;
	is_bullet_time = true;
	is_bullet_time_enable = true;
	is_player_mp_start = false;
	player_mp_taget = 0.0f;
	player_mp_start = player_mp;
	timer_bullet_time.pause();
	timer_bullet_time.restart();

}


void Player::move_on_bullet_time_end()
{
	if (!is_bullet_time_enable) return;
	is_bullet_time_enable = false;
	taget_bullet_time = 1.0f;
	taget_brighness = 1.0f;
	timer_bullet_time.resume();
	timer_bullet_time.restart();
	player_mp_taget = 100.0f;
	player_mp_start = player_mp;
}


void Player::on_hurt(DamageInfo damage_info)
{
	if(is_rolling || is_invincible || player_hp <= 0) return;
	is_invincible = true;
	timer_invincible.set_wait_time(damage_info.invincible_time);
	timer_invincible.restart();
	player_hp -= damage_info.damage;
	if (player_hp <= 0)
	{
		player_hp = 0;
	}
	AudioManager::GetInstance().PlaySoundAudio("res/audio/player/player_hurt.mp3", AudioManager::AudioType::Effect, 100);
}


void Player::on_land()
{
	//播放音效和特效
	AudioManager::GetInstance().PlaySoundAudio("res/audio/player/player_land.mp3", AudioManager::AudioType::Effect, 50);
	Vector2 effect_pos = { 0,0 };
	if (get_is_face_rigth())
		effect_pos = { get_collision_position().x - 75,get_collision_position().y - 135 };
	else
		effect_pos = { get_collision_position().x - 60,get_collision_position().y - 135 };

	ParticleManager::getInstance().createParticleInstance<LandEffect>(effect_pos, 100);
}


void Player::on_Possess()
{
	if (!wd_player || get_own_controller() == nullptr) return;
	WidgetManager::GetInstance().addToView(wd_player, get_own_controller());

}


void Player::on_UnPossess()
{
	if (!wd_player) return;
	WidgetManager::GetInstance().removeFromView(wd_player);
}


bool Player::reduce_stamina(float value)
{
	if (player_stamina < value) return false;
	player_stamina -= value;
	player_stamina_start = player_stamina;
	timer_player_stamina_start.restart();
	is_player_stamina_start = false;
	return true;
}
