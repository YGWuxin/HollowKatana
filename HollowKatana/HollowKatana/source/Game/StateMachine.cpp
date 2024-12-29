#include "StateMachine.h"
#include "StateNode.h"

void StateMachine::on_update(float delta)
{
	if (!current_state)
		return;
	if (needInit)
	{
		current_state->on_enter();
		needInit = false;
	}
	current_state->on_update(delta);
}

void StateMachine::set_entry(const string& id)
{
	current_state = state_pool[id];
}


void StateMachine::switch_to(const string& id)
{
	if (current_state)
		current_state->on_exit();
	current_state = state_pool[id];
	current_state->on_enter();
}


void StateMachine::register_state(const string& id, StateNode* state_node)
{
	state_pool[id] = state_node;
	state_node->set_own_state_machine(this);
}







