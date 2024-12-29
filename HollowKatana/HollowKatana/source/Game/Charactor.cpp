#include "Charactor.h"
#include "StateMachine.h"
#include "ActorObject.h"
#include "RenderManager.h"

Charactor::Charactor(Vector2 position) :Pawn(position)
{
	set_enable_gravity(true);
	set_render_layer(LAYER_ITEM_PLAYER);
	state_machine = new StateMachine();
	state_machine->set_own_charactor(this);
}


Charactor::~Charactor()
{
	if(state_machine)
		delete state_machine;
}



void Charactor::on_update(float delta)
{
	ActorObject::on_update(delta);
	if (state_machine)
		state_machine->on_update(delta);

	if (own_controller)
	{
		int direction = is_right_key_down - is_left_key_down;
		if (direction != 0 && is_move_lock == false)
		{
			is_face_rigth = direction > 0;
		}
		if (!is_move_lock)
			velocity.x = direction * run_velocity;					//ˮƽ�����ϵ��ٶ�

		//printf("Velocity: %0.1f, %0.1f\n", velocity.x, velocity.y);
	}
}


/* �����ƶ� */
void Charactor::Move_right_start()
{
	if(!is_right_key_down)
		is_right_key_down = true;
}

void Charactor::Move_right_stop()
{
	if(is_right_key_down)
		is_right_key_down = false;
}


/* �����ƶ� */
void Charactor::Move_left_start()
{
	if (!is_left_key_down)
		is_left_key_down = true;
}

void Charactor::Move_left_stop()
{
	if (is_left_key_down)
		is_left_key_down = false;
}

/* ��Ծ */
void Charactor::Move_jump()
{
	if (velocity.y != 0)
		return;
	velocity.y += jump_velocity;
}