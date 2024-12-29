#pragma once
#include "Pawn.h"

class ActorManager;
class Controller;
class PlayerController;
class StateMachine;

class Charactor : public Pawn
{
	friend class ActorManager;
	friend class PlayerController;
	friend class Controller;

protected:
	Charactor(Vector2 position);

	~Charactor();

	void on_update(float delta) override;

	void init_input_event() override {};


protected:
	//角色移动相关
	void Move_right_start();
	void Move_right_stop();
	void Move_left_start();
	void Move_left_stop();
	void Move_jump();

public:
	void set_run_velocity(float velocity) { run_velocity = velocity; }

	void set_jump_velocity(float velocity) { jump_velocity = velocity; }

	void set_is_move_lock(bool lock) { is_move_lock = lock; }

protected:
	StateMachine* state_machine = nullptr;		//需要要手动销毁

	float jump_velocity = -0.75f;
	float run_velocity = 0.45f;					//跑动速度
	bool on_jump = false;

	//如果是按键
	bool is_right_key_down = false;				//向右按键按下
	bool is_left_key_down = false;				//向左按键按下

	//禁止移动
	bool is_move_lock = false;





};

