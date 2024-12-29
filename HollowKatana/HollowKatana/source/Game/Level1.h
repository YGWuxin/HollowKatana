#pragma once
#include "Scene.h"
#include "Vector2.h"
#include "../Utils/Timer.h"
#include <graphics.h>	

class Camera;
class Charactor;
class Player;
//class Controller;
class RenderItem;
class Animation;
class IMAGE;
class ActorObject;
class Hornet;


class Level1 : public Scene
{
public:
	Level1() = default;
	~Level1() = default;

	void on_enter() override;

	void on_update(int delta) override;

	void on_input(const ExMessage& msg) override;

	void on_exit() override;

private:
	const char* bg_bgm = nullptr;

	//µØ°å
	ActorObject* floor = nullptr;

	ActorObject* wall1 = nullptr;
	ActorObject* wall2 = nullptr;

	Player* player_charactor = nullptr;

	Hornet* hornet = nullptr;


	Timer timer_over_player_death;

};

