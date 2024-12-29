#include "Level1.h"
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
#include "Charactor.h"
#include "Player.h"
#include "Sword.h"
#include "Barb.h"
#include "Hornet.h"


void Level1::on_enter()
{
	//设置默认相机
	default_camera.reset();
	SceneManager::GetInstance().set_main_camera(&default_camera);

	ResourcesManager& resources_manger = ResourcesManager::GetInstance();
	
	CollisionManager::GetInstance().set_enabled_debug(false);

	PlayerController* player1_controller = ControllerManager::GetInstance().get_player(ControllerManager::PlayerType::Player_1);

	bg_bgm = AudioManager::GetInstance().PlaySoundAudio("res/audio/ui/bgm.mp3", AudioManager::AudioType::Music, true);

	//创建背景
	ImageInfo* bg_image = ResourcesManager::GetInstance().find_image("img_level1_bg");
	RenderManager::getInstance().createRenderItem(bg_image,Vector2(WIN_WIDTH / 2, WIN_HEIGHT / 2),1);

	floor = ActorManager::GetInstance().create_actor<ActorObject>(Vector2(WIN_WIDTH / 2, WIN_HEIGHT - 60));
	floor->set_collision_size({ WIN_WIDTH + 100,80 });
	floor->set_collision_layer_self(CollisionLayer::PlatformLarge);

	wall1 = ActorManager::GetInstance().create_actor<ActorObject>(Vector2(-10, WIN_HEIGHT / 2));
	wall1->set_collision_size({ 10,WIN_HEIGHT });
	wall1->set_collision_layer_self(CollisionLayer::AirWall);

	wall2 = ActorManager::GetInstance().create_actor<ActorObject>(Vector2(WIN_WIDTH + 10, WIN_HEIGHT / 2));
	wall2->set_collision_size({ 10,WIN_HEIGHT });
	wall2->set_collision_layer_self(CollisionLayer::AirWall);

	player_charactor = ActorManager::GetInstance().create_actor<Player>(Vector2(200,400));
	player1_controller->Possess(player_charactor);

	hornet = ActorManager::GetInstance().create_actor<Hornet>(Vector2(WIN_WIDTH - 300, 400));
	hornet->set_is_face_rigth(false);
	hornet->set_target(player_charactor);

	timer_over_player_death.set_wait_time(2000);
	timer_over_player_death.restart();
	timer_over_player_death.set_one_shot(true);
	timer_over_player_death.set_callback([&](){
		SceneManager::GetInstance().switch_to(SceneManager::SceneType::Menu);
		});

}


void  Level1::on_update(int delta)
{
	if(player_charactor->get_is_dead() || hornet->get_hp() <= 0)
		timer_over_player_death.on_update(delta);
};

void  Level1::on_input(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		if (msg.vkcode == 'Q')
		{
			CollisionManager& collision_mangaer = CollisionManager::GetInstance();
			if (collision_mangaer.get_enabled_debug())
			{
				collision_mangaer.set_enabled_debug(false);
			}
			else
			{
				collision_mangaer.set_enabled_debug(true);
			}
		}
		if (msg.vkcode == 'P')
		{
			SceneManager::GetInstance().switch_to(SceneManager::SceneType::Menu);
		}
		
	}
};


void  Level1::on_exit()
{
	AudioManager::GetInstance().StopSound(bg_bgm);



};









