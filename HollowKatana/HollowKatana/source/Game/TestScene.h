#pragma once
#include "Scene.h"
#include "Vector2.h"
#include "../Utils/Timer.h"
#include <graphics.h>	

class Camera;
//class Character;
//class Controller;
class RenderItem;
class Animation;
class IMAGE;
class ActorObject;


class TestScene :  public Scene
{
public:
	TestScene() = default;
	~TestScene() = default;

	void on_enter() override;

	void on_update(int delta) override;

	void on_input(const ExMessage& msg) override;

	void on_exit() override;

	void test_3();

	void test_2();

	void test_1();

	void test_move_right_up();

	void test_move_right_down();

	void test_move_left_up();

	void test_move_left_down();

private:
	IMAGE img_test;
	ActorObject* ActorObject_Test = nullptr;
	ActorObject* ActorObject_Test1 = nullptr;
	ActorObject* ActorObject_Test2 = nullptr;


	Animation* Animation_Test = nullptr;

};

