#include "TestScene.h"
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
#include "TestWidget.h"
#include "WD_Player.h"
#include "WD_Hornet.h"

void TestScene::on_enter()
{
	//设置默认相机
	default_camera.reset();
	SceneManager::GetInstance().set_main_camera(&default_camera);



	RenderManager& render_manger = RenderManager::getInstance();
	ResourcesManager& resources_manger = ResourcesManager::GetInstance();

	CollisionManager::GetInstance().set_enabled_debug(true);

	ImageInfo* image_info = resources_manger.find_image("img_player_idle");
	Atlas* atlas = resources_manger.find_atlas("atlas_Hornet_idle");

	/*
	loadimage(&img_test,_T("res/character/player/idle.png"));
	*/

	PlayerController* player = ControllerManager::GetInstance().get_player(ControllerManager::PlayerType::Player_1);
	if (player)
	{
		player->clear_input_event_map();
		player->add_input_event_map('W', Pawn::KeyState::KEY_DOWN, bind(&TestScene::test_1, this));
		player->add_input_event_map('D', Pawn::KeyState::KEY_DOWN, bind(&TestScene::test_move_right_down, this));
		player->add_input_event_map('D', Pawn::KeyState::KEY_UP, bind(&TestScene::test_move_right_up, this));
		player->add_input_event_map('A', Pawn::KeyState::KEY_DOWN, bind(&TestScene::test_move_left_down, this));
		player->add_input_event_map('A', Pawn::KeyState::KEY_UP, bind(&TestScene::test_move_left_up, this));
		player->add_input_event_map('F', Pawn::KeyState::KEY_DOWN, bind(&TestScene::test_2, this));
		player->add_input_event_map('Q', Pawn::KeyState::KEY_DOWN, bind(&TestScene::test_3, this));
		//printf("add input event map\r\n");
	}

	//TestWidget* test_widget = WidgetManager::GetInstance().createUserWidgetInstance<TestWidget>(nullptr,1);
	//WidgetManager::GetInstance().addToView(test_widget, player);

	WD_Player* test_widget1 = WidgetManager::GetInstance().createUserWidgetInstance<WD_Player>(nullptr, 1);
	WidgetManager::GetInstance().addToView(test_widget1, player);

	WD_Hornet* test_widget2 = WidgetManager::GetInstance().createUserWidgetInstance<WD_Hornet>(nullptr, 1);
	WidgetManager::GetInstance().addToView(test_widget2, player);


	Animation_Test = new Animation();
	//Animation_Test->add_animation(image_info);
	Animation_Test->add_animation(atlas);
	Animation_Test->set_loop(true);
	Animation_Test->set_interval(80);


	ActorObject_Test = ActorManager::GetInstance().create_actor<ActorObject>(Vector2(800, 100));
	ActorObject_Test->set_current_animation_reset(Animation_Test);
	ActorObject_Test->set_collision_size({ 80,135 });
	ActorObject_Test->set_enable_gravity(true);
	ActorObject_Test->set_collision_layer_self(CollisionLayer::Player);
	ActorObject_Test->add_collision_layer(CollisionLayer::PlatformLarge);
	ActorObject_Test->add_collision_layer(CollisionLayer::PlatformSmall);
	//ActorObject_Test->set_velocity_x(-0.1f);

	//ActorObject_Test->set_enable_post_process(true);
	//ActorObject_Test->set_render_item_brightness(0.35f);

	ActorObject_Test1 = ActorManager::GetInstance().create_actor<ActorObject>(Vector2(WIN_WIDTH / 2, WIN_HEIGHT - 100));
	ActorObject_Test1->set_collision_size({ WIN_WIDTH - 10,80 });
	ActorObject_Test1->set_collision_layer_self(CollisionLayer::PlatformLarge);


	ActorObject_Test2 = ActorManager::GetInstance().create_actor<ActorObject>(Vector2(400, 300));
	ActorObject_Test2->set_collision_size({ 400,80 });
	ActorObject_Test2->set_collision_layer_self(CollisionLayer::PlatformSmall);
	ActorObject_Test2->add_collision_layer(CollisionLayer::Player);


	

};


void TestScene::test_3()
{
	SceneManager::GetInstance().switch_to(SceneManager::SceneType::Menu);
}


void TestScene::test_2()
{
	//ActorObject_Test->set_velocity_x(-0.2f);
	//ActorObject_Test->set_velocity_y(-0.8f);
	// 清空控制台
	system("cls");
}


void TestScene::test_1()
{
	//ActorObject_Test->set_velocity_x(-0.2f);
	ActorObject_Test->set_velocity_y(-0.8f);
}


void TestScene::test_move_right_up()
{
	ActorObject_Test->set_velocity_x(0);
}

void TestScene::test_move_right_down()
{
	ActorObject_Test->set_velocity_x(0.1f);
}

void TestScene::test_move_left_up()
{
	ActorObject_Test->set_velocity_x(0);
}

void TestScene::test_move_left_down()
{
	ActorObject_Test->set_velocity_x(-0.1f);

}




void  TestScene::on_update(int delta)
{
	//printf("测试主菜单场景\r\n");


};

void  TestScene::on_input(const ExMessage& msg)
{

	if (msg.message == WM_KEYDOWN)
	{
		//SceneManger::GetInstance().switch_to(SceneManger::SceneType::Select);
		//printf("测试主菜单场景\r\n");
		//SceneManger::GetInstance().QuitGame();
		//ActorObject_Test->set_velocity_y(-0.8f);
	}

};


void  TestScene::on_exit()
{

};