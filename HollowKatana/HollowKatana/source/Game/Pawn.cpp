#include "Pawn.h"
#include "CollisionManager.h"
#include "RenderManager.h"
#include "Controller.h"

Pawn::Pawn(Vector2 position): ActorObject(position)
{
	set_anchor_mode(AnchorMode::BottomCrented);
}

Pawn::~Pawn()
{
	if (own_controller)
	{
		own_controller->UnPossess(false);
	//	printf("Pawn Destructor\n");
	}
	
}


//添加输入事件
void Pawn::addInputEvent(string vk_code, function<void()> event, KeyState key_state)
{
	switch (key_state)
	{
	case Pawn::KeyState::KEY_UP:
		input_event_map_key_up[vk_code] = event;
		break;
	case Pawn::KeyState::KEY_DOWN:
		input_event_map_key_down[vk_code] = event;
		break;
	default:
		break;
	}
}

//执行输入事件
void Pawn::executeInputEvent(string vk_code, KeyState key_state)
{
	if (key_state == KeyState::KEY_UP)
	{
		auto it_up = input_event_map_key_up.find(vk_code);
		if (it_up != input_event_map_key_up.end()) {
			it_up->second();
		}
	}
	else if (key_state == KeyState::KEY_DOWN)
	{
		auto it_down = input_event_map_key_down.find(vk_code);
		if (it_down != input_event_map_key_down.end()) {
			it_down->second();
		}
	}
}


