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

	const float SPEED_DASH = 0.8f;		//����ٶ�
	const float SPEED_MOVE = 0.8f;		//����ٶ�


private:
	Timer timer_idle;						//����״̬��ʱ��
	Timer timer_aim;                        //��׼״̬��ʱ��
	int diff_period = 0;                    //��׼����
	bool is_vaild = true;                   //�Ƿ���Ч
	float total_delta_time = 0.0f;          //��ʱ��

	Vector2 base_position;                  //��׼λ��
	Vector2 target_position = {0,0};                  //���λ��

	Stage current_stage = Stage::Idle;               //��ǰ״̬

	Animation* animation_loose = nullptr;         //ʧȥ��������
	Animation* animation_break = nullptr;         //���鶯��

	function<void()> hit_callback;		//�����ص�

	float last_length = 0;

	int rand_distant = -1;

};

