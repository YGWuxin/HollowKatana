#include "MainMenuScene.h"
#include <iostream>
#include "SceneManager.h"
#include "ResourcesManager.h"
#include "AudioManager.h"
#include "Animation.h"
#include "Vector2.h"
#include "../Utils/helper.h"
#include "RenderManager.h"
#include "ActorObject.h"
#include "ActorManager.h"
#include "CollisionManager.h"
#include "../Parameter/GlobeGameParameters.h"
#include "PlayerController.h"
#include "ControllerManager.h"
#include "WidgetManager.h"
#include "MenuWidget.h"

void MainMenuScene::on_enter()
{
	//设置默认相机
	default_camera.reset();
	SceneManager::GetInstance().set_main_camera(&default_camera);

	PlayerController* player = ControllerManager::GetInstance().get_player(ControllerManager::PlayerType::Player_1);
	player->enable_input();
	
	MenuWidget* main_widget = WidgetManager::GetInstance().createUserWidgetInstance<MenuWidget>(nullptr, 1);
	WidgetManager::GetInstance().addToView(main_widget, player);


	menu_bg_bgm = AudioManager::GetInstance().PlaySoundAudio("res/audio/ui/menu_bgm.mp3", AudioManager::AudioType::Music, 50, true);

};


void  MainMenuScene::on_update(int delta)
{
	//printf("测试主菜单场景\r\n");
	
	
};

void  MainMenuScene::on_input(const ExMessage& msg)
{
	
	
	
};


void  MainMenuScene::on_exit()
{
	AudioManager::GetInstance().StopSound(menu_bg_bgm);
};



