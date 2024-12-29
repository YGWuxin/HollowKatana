#pragma once
#include "StateNode.h"
#include "Animation.h"
#include "../Utils/Timer.h"

class StateMachine;
class Hornet;

//���׶�Ѫ��
#define HORNET_STAGE2_HP 25
#define HORNET_STAGE1_HP 50


/* Hornet����״̬ */
class HornetIdleState : public StateNode
{
public:
	HornetIdleState();
	~HornetIdleState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation character_idle_animtaion_left;
	Animation character_idle_animtaion_right;
	Hornet* character = nullptr;
	Timer timer_idle;


};

/* Hornet����״̬ */
class HornetRunState : public StateNode
{
public:
	HornetRunState();
	~HornetRunState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
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

/* Hornet����״̬ */
class HornetFallState : public StateNode
{
public:
	HornetFallState();
	~HornetFallState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation character_fall_animtaion_left;
	Animation character_fall_animtaion_right;
	Hornet* character = nullptr;


};


/* Hornet��Ծ״̬ */
class HornetJumpState : public StateNode
{
public:
	HornetJumpState();
	~HornetJumpState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
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


/* Hornet��׼״̬ */
class HornetAimState : public StateNode
{
public:
	HornetAimState();
	~HornetAimState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation character_aim_animtaion_left;
	Animation character_aim_animtaion_right;
	Hornet* character = nullptr;

	bool is_aiming = false;
};


/* Hornet�¶�״̬ */
class HornetSquatState : public StateNode
{
public:
	HornetSquatState();
	~HornetSquatState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation character_squat_animtaion_left;
	Animation character_squat_animtaion_right;
	Hornet* character = nullptr;

	bool is_squatting = false;

};


/* Hornet���г��״̬ */
class HornetDashInAirState : public StateNode
{
public:
	HornetDashInAirState();
	~HornetDashInAirState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation character_dash_in_air_animtaion_left;
	Animation character_dash_in_air_animtaion_right;
	Hornet* character = nullptr;

};

/* Hornet������״̬ */
class HornetDashOnGroundState : public StateNode
{
public:
	HornetDashOnGroundState();
	~HornetDashOnGroundState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation character_dash_on_ground_animtaion_left;
	Animation character_dash_on_ground_animtaion_right;
	Hornet* character = nullptr;

	Timer timer_dash_on_floor;

};

/* Hornet�ӽ�״̬ */
class HornetThrowSwordState : public StateNode
{
public:
	HornetThrowSwordState();
	~HornetThrowSwordState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation character_thorw_sword_animtaion_left;
	Animation character_thorw_sword_animtaion_right;
	Hornet* character = nullptr;

	bool is_throwing_sword = false;
	bool is_lock_target = false;

};

/* Hornet��˿��״̬ */
class HornetThrowSilkState : public StateNode
{
public:
	HornetThrowSilkState();
	~HornetThrowSilkState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation character_thorw_silk_animtaion_left;
	Animation character_thorw_silk_animtaion_right;
	Hornet* character = nullptr;

	bool is_throwing_silk = false;

};

/* Hornet�Ӵ���״̬ */
class HornetThrowBarbState : public StateNode
{
public:
	HornetThrowBarbState();
	~HornetThrowBarbState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation character_thorw_barb_animtaion_left;
	Animation character_thorw_barb_animtaion_right;
	Hornet* character = nullptr;

	bool is_throwing_barb = false;
};


/* Hornet���״̬ */
class HornetHandLandState : public StateNode
{
public:
	HornetHandLandState();
	~HornetHandLandState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation character_hand_land_animtaion_left;
	Animation character_hand_land_animtaion_right;
	Hornet* character = nullptr;
	bool is_hand_landing = false;

};




/* Hornet����״̬ */
class HornetDeadState : public StateNode
{
public:
	HornetDeadState();
	~HornetDeadState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation character_dead_animtaion_left;
	Animation character_dead_animtaion_right;
	Hornet* character = nullptr;


};
