#pragma once
#include "ActorObject.h"

class ActorManager;
class Controller;
class PlayerController;

class Pawn :public ActorObject
{
	friend class ActorManager;
	friend class PlayerController;
	friend class Controller;

public:
	enum class KeyState
	{
		KEY_UP,
		KEY_DOWN,
		MOUSE_LEFT_DOWN,
		MOUSE_LEFT_UP,
		MOUSE_RIGHT_DOWN,
		MOUSE_RIGHT_UP,
	};

	struct DamageInfo
	{
		int damage = 0;
		Vector2 direction = Vector2(0,0);
		ActorObject* attacker = nullptr;
		//�޵�ʱ��
		float invincible_time = 0;
	};



public:
	//��ȡӵ�еĿ�����
	Controller* get_own_controller() const { return own_controller; }

	//��ʼ�������¼�
	virtual void init_input_event() {};

	virtual void on_hurt(DamageInfo damage_info) {};

	virtual void on_Possess() {};

	virtual void on_UnPossess() {};


protected:
	Pawn(Vector2 position);

	virtual ~Pawn();

	void on_update(float delta) override
	{
		ActorObject::on_update(delta);
	}

	//��������¼�
	void addInputEvent(string vk_code, function<void()> event, KeyState key_state);

	// ִ�������¼�����
	void executeInputEvent(string vk_code, KeyState key_state);


	//����ӵ�еĿ�����
	void set_own_controller(Controller* controller)
	{
		own_controller = controller;
		if (own_controller)
		{
			init_input_event();
		}

	}


private:
	unordered_map<string, function<void()>> input_event_map_key_down;
	unordered_map<string, function<void()>> input_event_map_key_up;

protected:
	//�ⲿ��ֵ������Ҫ����
	Controller* own_controller = nullptr;       //pawn�Ŀ�����


};

