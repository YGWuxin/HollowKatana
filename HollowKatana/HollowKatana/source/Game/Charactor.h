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
	//��ɫ�ƶ����
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
	StateMachine* state_machine = nullptr;		//��ҪҪ�ֶ�����

	float jump_velocity = -0.75f;
	float run_velocity = 0.45f;					//�ܶ��ٶ�
	bool on_jump = false;

	//����ǰ���
	bool is_right_key_down = false;				//���Ұ�������
	bool is_left_key_down = false;				//���󰴼�����

	//��ֹ�ƶ�
	bool is_move_lock = false;





};

