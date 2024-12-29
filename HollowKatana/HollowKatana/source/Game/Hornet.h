#pragma once
#include "Charactor.h"
#include "../Utils/Timer.h"

class ActorManager;
class StateMachine;
class Animation;
class WD_Hornet;

class Hornet :  public Charactor
{
	friend class ActorManager;
public:
	//冲刺类型
	enum class DashType
	{
		NONE,
		GROUND,
		AIR
	};

public:
	void on_hurt(DamageInfo damage_info) override;

	//生成刺球
	void generate_barbs();

	int get_barbs() {return barb_num;}

	//投掷剑
	void throw_sword();

	//丝线攻击
	void attack_silk();

	//冲刺攻击开始
	void attack_dash_start(DashType dash_type);

	//冲刺攻击结束
	void attack_dash_end(DashType dash_type);

	void set_target(Charactor* target) {
		this->target = nullptr;
		if(target)
			this->target = target;
	}

	Charactor* get_target() {return target;}

	bool get_is_dashing() {return is_dashing;}

	float get_target_distance_x() {return target_distance_x;}

	//获取生命值
	int get_hp() {return hp;}

	bool is_invincible_now() const { return is_invincible; };

	void set_is_last_face_right(bool is_right) { is_last_face_right = is_right; }

	bool get_is_last_face_right() const { return is_last_face_right; }

protected:
	Hornet(Vector2 position);

	~Hornet();

	void on_update(float delta) override;

	void on_land() override;

	void handleCollision(const HitInfo& hit_info) override;


private:
	ActorObject* attack_silk_box = nullptr;		//丝线攻击盒
	ActorObject* attack_dash_box = nullptr;		//冲刺攻击盒

	Animation* attack_effect_right = nullptr;  //攻击特效
	Animation* attack_effect_left = nullptr;   //攻击特效

	float attack_silk_pos_x_offset = 0.0f;		 //攻击盒的x轴偏移量
	float attack_silk_pos_y_offset = -75.0f;		 //攻击盒的y轴偏移量

	float attack_dash_pos_x_offset = 0.0f;		 //攻击盒的x轴偏移量
	float attack_dash_pos_y_offset = -75.0f;		 //攻击盒的y轴偏移量


	int barb_num = 0;								//刺球数量
	const int MAX_BARB_NUM = 6;						//最大刺球数量

	Charactor* target = nullptr;					//目标
	Vector2 target_pos = Vector2(0,0);							//目标位置


	//地面冲刺速度
	const float DASH_SPEED_GROUND = 1.5f;
	//空中冲刺速度
	const float DASH_SPEED_AIR = 2.5f;

	DashType dash_type = DashType::NONE;			//冲刺类型

	bool is_dashing = false;						//是否正在冲刺

	int hp = 100;									//生命值

	float target_distance_x = 0.0f;					//目标距离


	//是否处于无敌状态
	bool is_invincible = false;
	//无敌持续时间
	float invincible_time = 500.0f;


	Timer timer_invincible;						//无敌计时器
	Timer timer_invulnerable_blink;				//无敌状态闪烁定时器

	IMAGE* sketch_image = nullptr;
	ImageInfo sketch_image_info;

	bool is_showing_sketch_frame = false;		//当前帧是否应该显示剪影
	bool is_enable_sketch = false;				//是否开启剪影


	WD_Hornet* wd_hornet = nullptr;

	bool is_last_face_right = true;				//上一帧是否右面朝向
};

