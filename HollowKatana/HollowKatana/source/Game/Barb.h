#pragma once
#include "ActorObject.h"
#include "../Utils/Timer.h"


class ActorManager;
class Animation;

class Barb : public ActorObject
{
	friend class ActorManager;

public:
	bool check_vaild()
	{
		return is_vaild;
	}

	void set_hit_callback(function<void()> callback)
	{
		hit_callback = callback;
	}


	void set_move_target(Vector2 target);


protected:
	Barb(Vector2 position);

	virtual ~Barb();

	void on_update(float delta) override;

	void handleCollision(const HitInfo& hit_info) override;

private:
	void on_break();


private:
	enum class Stage
	{
		Move,
		Idle,
		Aim,
		Dash,
		Break
	};

	const float SPEED_DASH = 0.8f;		//冲刺速度
	const float SPEED_MOVE = 0.8f;		//冲刺速度


private:
	Timer timer_idle;						//空闲状态计时器
	Timer timer_aim;                        //瞄准状态计时器
	int diff_period = 0;                    //瞄准周期
	bool is_vaild = true;                   //是否有效
	float total_delta_time = 0.0f;          //总时间

	Vector2 base_position;                  //基准位置
	Vector2 target_position = {0,0};                  //冲刺位置

	Stage current_stage = Stage::Idle;               //当前状态

	Animation* animation_loose = nullptr;         //失去生命动画
	Animation* animation_break = nullptr;         //破碎动画

	function<void()> hit_callback;		//触发回调

	float last_length = 0;

	int rand_distant = -1;

};

