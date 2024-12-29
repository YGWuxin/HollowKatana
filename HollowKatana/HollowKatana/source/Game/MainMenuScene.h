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

class MainMenuScene : public Scene
{
public:
	MainMenuScene() = default;
	~MainMenuScene() = default;

	void on_enter() override;

	void on_update(int delta) override;

	void on_input(const ExMessage& msg) override;

	void on_exit() override;

private:
	const char* menu_bg_bgm = nullptr;




};

