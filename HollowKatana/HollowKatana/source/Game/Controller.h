#pragma once
#include <graphics.h>	
#include <cstdio>

using namespace std;

class ControllerManager;
class Pawn;

class Controller
{
	friend class ControllerManager;

public:
	//设置被控制的Pawn
	virtual void Possess(Pawn* Pawn);

	//获取被控制的Pawn
	Pawn* get_owned_character() { return ControlledPawn; }

	//解除被控制的Pawn
	virtual void UnPossess(bool isDestroy = false);

	void disable_input() { can_input = false; }

	void enable_input() { can_input = true; }

	bool get_can_input() { return can_input; }

protected:
	virtual void on_update(float delta) {}

	//检查控制器的输入事件
	virtual void check_input(const ExMessage& msg) {}


protected:
	Controller() = default;
	~Controller() = default;


	
protected:
	bool can_input = true;
	Pawn* ControlledPawn = nullptr;

};
