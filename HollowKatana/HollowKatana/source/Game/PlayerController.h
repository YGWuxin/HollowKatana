#pragma once
#include "Controller.h"
#include <graphics.h>	
#include <string>
#include <functional>
#include <vector>
#include "Pawn.h"

class ControllerManager;
class UserWidget;

class PlayerController :  public Controller
{
	friend class ControllerManager;

protected:
	PlayerController() = default;
	~PlayerController() = default;


public:
	void add_input_event_map(int vk_code, Pawn::KeyState key_state, function<void()> event);
	void add_input_event_map(int vk_code, string event_name, Pawn::KeyState key_state);

	void clear_input_event_map() { InputEventMap_List.clear(); }

	void check_input(const ExMessage& msg) override;

	void Possess(Pawn* Pawn) override;

	void UnPossess(bool isDestroy = false) override;

private:
	struct InputEventMap
	{
		int vk_code;
		string event_name;
		Pawn::KeyState key_state;
		function<void()> event;
		InputEventMap(int code, const string name, Pawn::KeyState state, function<void()> ev)
			: vk_code(code), event_name(name), key_state(state), event(ev) {}
	};
	std::vector<InputEventMap> InputEventMap_List;

};

