#pragma once
#include "StateNode.h"
#include "Animation.h"
#include "../Utils/Timer.h"

class StateMachine;
class Hornet;

//二阶段血量
#define HORNET_STAGE2_HP 25
#define HORNET_STAGE1_HP 50


/* Hornet闲置状态 */
class HornetIdleState : public StateNode
{
public:
	HornetIdleState();
	~HornetIdleState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_idle_animtaion_left;
	Animation character_idle_animtaion_right;
	Hornet* character = nullptr;
	Timer timer_idle;


};

/* Hornet奔跑状态 */
class HornetRunState : public StateNode
{
public:
	HornetRunState();
	~HornetRunState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_run_animtaion_left;
	Animation character_run_animtaion_right;
	Hornet* character = nullptr;

	const float MIN_SILK_ATTACK_DISTANCE = 130.0f;
	const float MIN_DASH_ATTACK_DISTANCE = 300.0f;

	const float RUN_SPEED = 0.4f;

	int rand_num = -1;

	const char* run_sound = nullptr;

};

/* Hornet掉落状态 */
class HornetFallState : public StateNode
{
public:
	HornetFallState();
	~HornetFallState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_fall_animtaion_left;
	Animation character_fall_animtaion_right;
	Hornet* character = nullptr;


};


/* Hornet跳跃状态 */
class HornetJumpState : public StateNode
{
public:
	HornetJumpState();
	~HornetJumpState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;

private:
	enum NextState
	{
		STATE_NONE,
		STATE_AIM,
		STATE_ATTACK_SILK,
		STATE_FALL
	};


private:
	Animation character_jump_animtaion_left;
	Animation character_jump_animtaion_right;
	Hornet* character = nullptr;

	NextState next_state = STATE_NONE;
	int rand_num = -1;

	Timer timer_jump;
	bool is_jumping = false;
};


/* Hornet瞄准状态 */
class HornetAimState : public StateNode
{
public:
	HornetAimState();
	~HornetAimState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_aim_animtaion_left;
	Animation character_aim_animtaion_right;
	Hornet* character = nullptr;

	bool is_aiming = false;
};


/* Hornet下蹲状态 */
class HornetSquatState : public StateNode
{
public:
	HornetSquatState();
	~HornetSquatState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_squat_animtaion_left;
	Animation character_squat_animtaion_right;
	Hornet* character = nullptr;

	bool is_squatting = false;

};


/* Hornet空中冲刺状态 */
class HornetDashInAirState : public StateNode
{
public:
	HornetDashInAirState();
	~HornetDashInAirState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_dash_in_air_animtaion_left;
	Animation character_dash_in_air_animtaion_right;
	Hornet* character = nullptr;

};

/* Hornet地面冲刺状态 */
class HornetDashOnGroundState : public StateNode
{
public:
	HornetDashOnGroundState();
	~HornetDashOnGroundState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_dash_on_ground_animtaion_left;
	Animation character_dash_on_ground_animtaion_right;
	Hornet* character = nullptr;

	Timer timer_dash_on_floor;

};

/* Hornet扔剑状态 */
class HornetThrowSwordState : public StateNode
{
public:
	HornetThrowSwordState();
	~HornetThrowSwordState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_thorw_sword_animtaion_left;
	Animation character_thorw_sword_animtaion_right;
	Hornet* character = nullptr;

	bool is_throwing_sword = false;
	bool is_lock_target = false;

};

/* Hornet扔丝线状态 */
class HornetThrowSilkState : public StateNode
{
public:
	HornetThrowSilkState();
	~HornetThrowSilkState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_thorw_silk_animtaion_left;
	Animation character_thorw_silk_animtaion_right;
	Hornet* character = nullptr;

	bool is_throwing_silk = false;

};

/* Hornet扔刺球状态 */
class HornetThrowBarbState : public StateNode
{
public:
	HornetThrowBarbState();
	~HornetThrowBarbState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_thorw_barb_animtaion_left;
	Animation character_thorw_barb_animtaion_right;
	Hornet* character = nullptr;

	bool is_throwing_barb = false;
};


/* Hornet落地状态 */
class HornetHandLandState : public StateNode
{
public:
	HornetHandLandState();
	~HornetHandLandState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_hand_land_animtaion_left;
	Animation character_hand_land_animtaion_right;
	Hornet* character = nullptr;
	bool is_hand_landing = false;

};




/* Hornet死亡状态 */
class HornetDeadState : public StateNode
{
public:
	HornetDeadState();
	~HornetDeadState() = default;

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation character_dead_animtaion_left;
	Animation character_dead_animtaion_right;
	Hornet* character = nullptr;


};
