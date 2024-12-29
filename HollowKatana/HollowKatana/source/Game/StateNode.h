#pragma once

class StateMachine;

class StateNode
{
public:
	StateNode() = default;
	~StateNode() = default;

	//״̬���뺯��
	virtual void on_enter() {};

	//״̬���º���
	virtual void on_update(float delta) {};

	//״̬�˳�ʱ����
	virtual void on_exit() {};

	//����״̬��
	void set_own_state_machine(StateMachine* state_machine) { own_state_machine = state_machine; }

protected:
	StateMachine* own_state_machine = nullptr;
	bool loadedAnimation = false;

private:
	


};

