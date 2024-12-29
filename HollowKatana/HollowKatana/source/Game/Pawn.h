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
		//无敌时间
		float invincible_time = 0;
	};



public:
	//获取拥有的控制器
	Controller* get_own_controller() const { return own_controller; }

	//初始化输入事件
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

	//添加输入事件
	void addInputEvent(string vk_code, function<void()> event, KeyState key_state);

	// 执行输入事件任务
	void executeInputEvent(string vk_code, KeyState key_state);


	//设置拥有的控制器
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
	//外部赋值，不需要销毁
	Controller* own_controller = nullptr;       //pawn的控制器


};

