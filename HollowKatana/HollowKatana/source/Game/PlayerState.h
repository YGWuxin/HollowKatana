#pragma once
#include "StateNode.h"
#include "Animation.h"

class StateMachine;
class Player;

class PlayerIdleState : public StateNode
{
public:
	PlayerIdleState();
	~PlayerIdleState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation player_idle_animtaion_left;
	Animation player_idle_animtaion_right;
	Player* character = nullptr;
};



class PlayerRunState : public StateNode
{
public:
	PlayerRunState();
	~PlayerRunState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation player_run_animtaion_left;
	Animation player_run_animtaion_right;
	Player* character = nullptr;

	const char* run_sound = nullptr;

};



class PlayerJumpState : public StateNode
{
public:
	PlayerJumpState();
	~PlayerJumpState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation player_jump_animtaion_left;
	Animation player_jump_animtaion_right;
	Player* character = nullptr;

	const char* jump_sound = nullptr;

	bool is_jumping = false;

};



class PlayerFallState : public StateNode
{
public:
	PlayerFallState();
	~PlayerFallState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation player_fall_animtaion_left;
	Animation player_fall_animtaion_right;
	Player* character = nullptr;

	const char* fall_sound = nullptr;
};



class PlayerRollState : public StateNode
{
public:
	PlayerRollState();
	~PlayerRollState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation player_roll_animtaion_left;
	Animation player_roll_animtaion_right;
	Player* character = nullptr;

	const char* roll_sound = nullptr;
};



class PlayerAttackState : public StateNode
{
public:
	PlayerAttackState();
	~PlayerAttackState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation player_attack_animtaion_left;
	Animation player_attack_animtaion_right;
	Player* character = nullptr;

	//const char* roll_sound = nullptr;
};


class PlayerDeadState : public StateNode
{
public:
	PlayerDeadState();
	~PlayerDeadState() = default;

	//״̬���뺯��
	void on_enter() override;

	//״̬���º���
	void on_update(float delta)  override;

	//״̬�˳�ʱ����
	void on_exit() override;


private:
	Animation player_dead_animtaion_left;
	Animation player_dead_animtaion_right;
	Player* character = nullptr;

	//const char* roll_sound = nullptr;
};

