#include "ControllerManager.h"
#include "Controller.h"
#include "PlayerController.h"

using namespace std;


void ControllerManager::create_player(const PlayerType& type)
{
	//如果已经创建则返回不用创建
	if (player_list[type])
		return;
	Controller* player = nullptr;
	player = new PlayerController();

	player_list[type] = player;
}


void ControllerManager::update_player_input_mapping(const PlayerType& type)
{
	PlayerController* player = dynamic_cast<PlayerController*>(player_list[type]);	// 尝试转换父类指针为子类指针
	if(!player)
		return;

	player->clear_input_event_map();   //清空按键事件映射
	player->add_input_event_map('D', "move_right", Pawn::KeyState::KEY_DOWN);			//按下D键执行角色中标签为move_right的函数事件	
	player->add_input_event_map('D', "move_right", Pawn::KeyState::KEY_UP);

	player->add_input_event_map('A', "move_left", Pawn::KeyState::KEY_DOWN);
	player->add_input_event_map('A', "move_left", Pawn::KeyState::KEY_UP);

	player->add_input_event_map('W', "jump", Pawn::KeyState::KEY_DOWN);
	player->add_input_event_map('W', "jump", Pawn::KeyState::KEY_UP);

	player->add_input_event_map('S', "crouch", Pawn::KeyState::KEY_DOWN);
	player->add_input_event_map('S', "crouch", Pawn::KeyState::KEY_UP);

	player->add_input_event_map(VK_SPACE, "roll", Pawn::KeyState::KEY_DOWN);
	player->add_input_event_map(VK_SPACE, "roll", Pawn::KeyState::KEY_UP);

	player->add_input_event_map(WM_LBUTTONDOWN, "attack", Pawn::KeyState::KEY_DOWN);

	player->add_input_event_map(WM_RBUTTONDOWN, "bullet_time", Pawn::KeyState::KEY_DOWN);
	player->add_input_event_map(WM_RBUTTONUP, "bullet_time", Pawn::KeyState::KEY_UP);
}


PlayerController* ControllerManager::get_player(const PlayerType& type)
{
	PlayerController* player = dynamic_cast<PlayerController*>(player_list[type]);	// 尝试转换父类指针为子类指针
	if(player)
		return player;
	return nullptr;
}


void ControllerManager::on_update(float delta)
{
	//更新所有玩家控制器
	for (auto it = player_list.begin(); it != player_list.end(); ++it) {
		Controller* player = it->second;  // 获取 Controller* 指针
		if (player)
			player->on_update(delta);
	}

	//更新AI控制器
	for (auto& ai : ai_list) 
	{
		if(ai)
			ai->on_update(delta);
	}

}


void ControllerManager::on_input(const ExMessage& msg)
{
	
	for (auto it = player_list.begin(); it != player_list.end(); ++it) {
		Controller* player = it->second;  // 获取 Controller* 指针
		if (player)
		{
			//printf("Checking input for controller: %s\n", typeid(*player).name());
			player->check_input(msg);
		}
	}
}



//创建AI控制器
void ControllerManager::create_ai_controller()
{

}

//删除AI控制器 
void ControllerManager::remove_ai_controller()
{

}

