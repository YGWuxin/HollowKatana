#pragma once
#include <string>
#include "StateNode.h"
#include <unordered_map>


using namespace std;

class Charactor;

class StateMachine
{
public:
	StateMachine() = default;
	~StateMachine() {
		// ���� unordered_map ��ɾ������ָ��
		for (auto& pair : state_pool) {
			delete pair.second; // ɾ��ָ��ָ��Ķ���
		}
		// ��� map
		state_pool.clear();
	};

	void on_update(float delta);

	void set_entry(const string& id);

	void switch_to(const string& id);

	void register_state(const string& id, StateNode* state_node);

	void set_own_charactor(Charactor* charactor)
	{
		own_charactor = charactor;
	}

	Charactor* get_own_charactor() const
	{
		return own_charactor;
	}

private:
	bool needInit = true;
	StateNode* current_state = nullptr;
	unordered_map<string, StateNode*> state_pool;
	Charactor* own_charactor = nullptr;

};




