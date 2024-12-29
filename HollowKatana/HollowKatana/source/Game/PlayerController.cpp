#include "PlayerController.h"
#include "WidgetManager.h"

void PlayerController::check_input(const ExMessage& msg)
{
	if (!can_input)
		return;
	//printf("PlayerController::check_input\n");
	if (msg.message == WM_KEYUP)
	{
		for (std::vector<InputEventMap>::const_iterator it = InputEventMap_List.cbegin(); it != InputEventMap_List.cend(); ++it) {
			if (msg.vkcode != it->vk_code || it->key_state != Pawn::KeyState::KEY_UP) {
				continue;
			}
			if (it->event)
			{
				it->event();
			}
			if (ControlledPawn)
			{
				ControlledPawn->executeInputEvent(it->event_name, Pawn::KeyState::KEY_UP);
			}
		}
	}
	else if (msg.message == WM_KEYDOWN)
	{
		for (std::vector<InputEventMap>::const_iterator it = InputEventMap_List.cbegin(); it != InputEventMap_List.cend(); ++it) {
			if (msg.vkcode != it->vk_code || it->key_state != Pawn::KeyState::KEY_DOWN) {
				continue;
			}
			if (it->event)
			{
				it->event();
			}
			if (ControlledPawn)
			{
				ControlledPawn->executeInputEvent(it->event_name, Pawn::KeyState::KEY_DOWN);
			}
		}
	}
	else if (msg.message == WM_LBUTTONDOWN || msg.message == WM_RBUTTONDOWN)   // 鼠标按下
	{
		for (std::vector<InputEventMap>::const_iterator it = InputEventMap_List.cbegin(); it != InputEventMap_List.cend(); ++it) {
			if (msg.message != it->vk_code || it->key_state != Pawn::KeyState::KEY_DOWN) {
				continue;
			}
			if (it->event)
			{
				it->event();
			}
			if (ControlledPawn)
			{
				ControlledPawn->executeInputEvent(it->event_name, Pawn::KeyState::KEY_DOWN);
			}
		}
	}
	else if (msg.message == WM_LBUTTONUP || msg.message == WM_RBUTTONUP)     // 鼠标抬起
	{
		for (std::vector<InputEventMap>::const_iterator it = InputEventMap_List.cbegin(); it != InputEventMap_List.cend(); ++it) {
			if (msg.message != it->vk_code || it->key_state != Pawn::KeyState::KEY_UP) {
				continue;
			}
			if (it->event)
			{
				it->event();
			}
			if (ControlledPawn)
			{
				ControlledPawn->executeInputEvent(it->event_name, Pawn::KeyState::KEY_UP);
			}
		}
	}
	
}


void PlayerController::add_input_event_map(int vk_code, Pawn::KeyState key_state, function<void()> event)
{
	InputEventMap_List.emplace_back(vk_code, "NULL", key_state, event);
}


void PlayerController::add_input_event_map(int vk_code, string event_name, Pawn::KeyState key_state)
{
	InputEventMap_List.emplace_back(vk_code, event_name, key_state, nullptr);
}



void PlayerController::Possess(Pawn* Pawn)
{
	Controller::Possess(Pawn);
	enable_input();
	//clear_input_event_map();
}

void PlayerController::UnPossess(bool isDestroy)
{
	Controller::UnPossess(isDestroy);
	//clear_input_event_map();
}

