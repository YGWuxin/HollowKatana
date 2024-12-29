#pragma once
#include "Charactor.h"
#include "../Utils/Timer.h"
#include "Camera.h"


class ActorManager;
class Controller;
class PlayerController;
class StateMachine;
class Animation;
class WD_Player;

class Player : public Charactor
{
	friend class ActorManager;
	friend class PlayerController;
	friend class Controller;

public:
	void init_input_event() override;

	bool is_rolling_now() const { return is_rolling; };

	bool is_invincible_now() const { return is_invincible; };

	void set_is_invincible_now(bool value) { 
		this->is_invincible = value;
		if (value)
			is_enable_sketch = false;
		else
			is_enable_sketch = true;
	};

	bool get_is_attacking() const { return is_attacking; };

	void set_is_attacking(bool value) { is_attacking = value; };

	void on_hurt(DamageInfo damage_info) override;

	void on_Possess() override;

	void on_UnPossess() override;

	int get_hp() {return player_hp; }

	void set_is_dead(bool value) { is_dead = value; };

	bool get_is_dead() const { return is_dead; };

	Camera* get_camera() { return &player_camera; };

	WD_Player* get_wd_player() { return wd_player; };

protected:
	Player(Vector2 position);

	~Player();

	void on_update(float delta) override;

	void on_land() override;

	

protected:
	void move_right_down();

	void move_right_up();

	void move_left_down();

	void move_left_up();

	void move_on_jump_down();

	void move_on_jump_up();

	void move_on_crouch_down();

	void move_on_crouch_up();


	void move_roll_down();

	void move_roll_up();

	void move_on_attack();

	void move_on_bullet_time_start();

	void move_on_bullet_time_end();

	//减少体力
	bool reduce_stamina(float value);

private:
	Timer timer_roll;

	bool is_rolling = false;     //是否翻滚
	bool is_key_rolling_dowm = false;  //是否翻滚下

	bool is_attacking = false;   //是否攻击


	float roll_time = 400.0f;  //翻滚持续时间
	float roll_speed = 0.9f;   //翻滚速度

	ActorObject* attack_box = nullptr;  //攻击盒

	Animation* attack_effect_right = nullptr;  //攻击特效
	Animation* attack_effect_left = nullptr;   //攻击特效
	Animation* attack_effect_up = nullptr;     //攻击特效
	Animation* attack_effect_down = nullptr;   //攻击特效


	float attack_box_pos_x_offset = 0.0f;		 //攻击盒的x轴偏移量
	float attack_box_pos_y_offset = 0.0f;		 //攻击盒的y轴偏移量

	bool is_up_key_pressed = false;
	bool is_down_key_pressed = false;


	float current_bullet_time = 1.0f;  //当前的子弹时间
	float taget_bullet_time = 1.0f;    //目标的子弹时间
	float current_brighness = 1.0f;    //当前的亮度
	float taget_brighness = 1.0f;      //目标的亮度
	float speed_factor = 5.0f;         //速度因子

	bool is_bullet_time = false;		//是否开始子弹时间
	bool is_bullet_time_enable = false;  //是否 enable 子弹时间

	//是否处于无敌状态
	bool is_invincible = false;
	//无敌持续时间
	float invincible_time = 500.0f;

	
	Timer timer_invincible;						//无敌计时器
	Timer timer_invulnerable_blink;				//无敌状态闪烁定时器

	IMAGE* sketch_image = nullptr;
	ImageInfo sketch_image_info;
	
	bool is_showing_sketch_frame = false;		//当前帧是否应该显示剪影
	bool is_enable_sketch = true;				//是否开启剪影

	WD_Player* wd_player = nullptr;				//玩家的UI


	int player_hp = 100;							//玩家的血量

	float player_stamina = 100;								//玩家的体力
	float player_stamina_start = 100;
	bool is_player_stamina_start = false;					//玩家体力恢复开始标志
	Timer timer_player_stamina_start;						//玩家的体力恢复计时器
	const float PLAYER_ROLL_STAMINA = 23.0f;				//玩家翻滚消耗的体力
	const float PLAYER_ATTACK_STAMINA = 7.0f;				//玩家攻击消耗的体力
	const float PLAYER_JUMP_STAMINA = 14.0f;				//玩家攻击消耗的体力

	const float PLAYER_STAMINA_RESTORE_TIME = 1500.0f;		//恢复的停留时间
	const float PLAYER_STAMINA_RESTORE_SPEED = 40.0f;		//恢复的速度

	float player_mp = 100;									//玩家的魔法值
	float player_mp_taget = 100;							//玩家的魔法值目标值
	float player_mp_start = 100;							//玩家的魔法值开始值
	Timer timer_bullet_time;								//子弹时间开始计时器
	const float PLAYER_MP_RESTORE_TIME = 2000.0f;			//子弹时间的停留时间
	const float PLAYER_MP_RESTORE_SPEED = 35.0f;			//恢复的速度
	const float PLAYER_MP_REDUCE_SPEED = 30.0f;				//减少的速度
	bool is_player_mp_start = false;						//玩家魔法恢复开始标志

	float strenth = 3;				//抖动强度
	int duration = 200;				//抖动间隔
	
	bool is_dead = false;			//是否死亡

	Camera player_camera;								//默认摄像机
	float camera_pos_x = 10.0f;							//摄像机移动速度
	float last_velocity_x = 0.0f;						//上一次的x轴速度
	Vector2 last_position;								//上一次的位置

};

