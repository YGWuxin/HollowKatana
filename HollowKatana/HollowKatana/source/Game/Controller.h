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
	//���ñ����Ƶ�Pawn
	virtual void Possess(Pawn* Pawn);

	//��ȡ�����Ƶ�Pawn
	Pawn* get_owned_character() { return ControlledPawn; }

	//��������Ƶ�Pawn
	virtual void UnPossess(bool isDestroy = false);

	void disable_input() { can_input = false; }

	void enable_input() { can_input = true; }

	bool get_can_input() { return can_input; }

protected:
	virtual void on_update(float delta) {}

	//���������������¼�
	virtual void check_input(const ExMessage& msg) {}


protected:
	Controller() = default;
	~Controller() = default;


	
protected:
	bool can_input = true;
	Pawn* ControlledPawn = nullptr;

};
