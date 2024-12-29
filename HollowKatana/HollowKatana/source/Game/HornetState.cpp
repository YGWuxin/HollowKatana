#include "HornetState.h"
#include "Hornet.h"
#include "StateMachine.h"
#include "ResourcesManager.h"
#include "AudioManager.h"
#include "ParticleManager.h"
#include "PlayerEffect.h"
#include  "Vector2.h"
#include "Player.h"
#include "Controller.h"
#include "WD_Player.h"

/**************************** 有关角色默认状态 ****************************************/
HornetIdleState::HornetIdleState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_idle_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_idle_right"));
	character_idle_animtaion_right.set_loop(true);
	character_idle_animtaion_right.set_interval(100);

	character_idle_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_idle_left"));
	character_idle_animtaion_left.set_loop(true);
	character_idle_animtaion_left.set_interval(100);

	timer_idle.set_one_shot(true);
	timer_idle.set_callback([&] {
		if(!character) return;
		int rand_num = rand() % 101; // 0-100
		if (character->get_hp() > HORNET_STAGE2_HP)
		{
			if (rand_num >= 0 && rand_num <= 25)
			{
				if(!character->get_on_ground())
					own_state_machine->switch_to("fall");
				else
					own_state_machine->switch_to("jump");
			}
			else if (rand_num > 25 && rand_num <= 50)
			{
				if (!character->get_on_ground())
					own_state_machine->switch_to("fall");
				else
					own_state_machine->switch_to("run");
			}
			else if(rand_num > 50 && rand_num <= 80)
				own_state_machine->switch_to("squat");
			else if (rand_num > 80 && rand_num <= 90)
				own_state_machine->switch_to("throw_silk");
			else if (rand_num > 90 && rand_num <= 100)
				own_state_machine->switch_to("throw_sword");
		}
		else
		{
			if (rand_num >= 0 && rand_num <= 25)
			{
				if (!character->get_on_ground())
					own_state_machine->switch_to("fall");
				else
					own_state_machine->switch_to("jump");
			}
			else if (rand_num > 25 && rand_num <= 60)
				own_state_machine->switch_to("throw_sword");
			else if (rand_num > 60 && rand_num <= 70)
				own_state_machine->switch_to("throw_silk");
			else if (rand_num > 70 && rand_num <= 90)
			{
				if(character->get_barbs() <= 15)
					own_state_machine->switch_to("throw_barb");
				else
					own_state_machine->switch_to("run");
			}
			else if (rand_num > 90 && rand_num <= 100)
				own_state_machine->switch_to("squat");
		}
		});
}

void HornetIdleState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &character_idle_animtaion_right : &character_idle_animtaion_left);


	character->set_velocity_x(0);

	float wait_time = 0.0f;

	if (character->get_hp() > HORNET_STAGE1_HP)
		wait_time = (rand() % 3 + 1) * 250.0f;			// 250-500ms
	else
		wait_time = (rand() % 2 ) * 250.0f;				// 0-250ms

	timer_idle.set_wait_time(wait_time);
	timer_idle.restart();

	//printf("Hornet当前状态：Idle\n");

}

void HornetIdleState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &character_idle_animtaion_right : &character_idle_animtaion_left);

	if (character->get_hp() <= 0)
		own_state_machine->switch_to("dead");
	else if(!character->get_on_ground())
		own_state_machine->switch_to("fall");

	Player* player = dynamic_cast<Player*>(character->get_target());
	if (player && player->get_hp() > 0)
	{
		timer_idle.on_update(delta);
	}


}

void HornetIdleState::on_exit()
{
	character_idle_animtaion_left.reset();
	character_idle_animtaion_right.reset();
}
/***************************************************************************************/



/**************************** 有关角色奔跑状态 ****************************************/
HornetRunState::HornetRunState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_run_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_run_right"));
	character_run_animtaion_right.set_loop(true);
	character_run_animtaion_right.set_interval(100);

	character_run_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_run_left"));
	character_run_animtaion_left.set_loop(true);
	character_run_animtaion_left.set_interval(100);

}

void HornetRunState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &character_run_animtaion_right : &character_run_animtaion_left);

	rand_num = rand() % 101; // 0-100

	run_sound = AudioManager::GetInstance().PlaySoundAudio("res/audio/enemy/enemy_run.mp3", AudioManager::AudioType::Effect, 80,true);

	//printf("Hornet当前状态：Run , rand_num = %d\n", rand_num);
}

void HornetRunState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &character_run_animtaion_right : &character_run_animtaion_left);

	character->set_velocity_x(character->get_is_face_rigth() ? RUN_SPEED : -RUN_SPEED);


	if (character->get_hp() <= 0)						// 角色死亡
	{
		own_state_machine->switch_to("dead");
		return;
	}
	else if (character->get_target_distance_x() <= 0)
	{
		own_state_machine->switch_to("idle");
		return;
	}
	else if (character->get_velocity().y > 0 && !character->get_on_ground())
	{
		own_state_machine->switch_to("fall");
		return;
	}

	if (character->get_hp() > HORNET_STAGE1_HP)
	{
		if (rand_num <= 25 && character->get_target_distance_x() <= MIN_DASH_ATTACK_DISTANCE)
			own_state_machine->switch_to("squat");
		else if (rand_num > 25 && rand_num <= 100 && character->get_target_distance_x() <= MIN_SILK_ATTACK_DISTANCE)
			own_state_machine->switch_to("throw_silk");
	}
	else
	{
		
		if (rand_num >= 0 && rand_num <= 50 && character->get_target_distance_x() <= MIN_SILK_ATTACK_DISTANCE)
			own_state_machine->switch_to("throw_silk");
		else if (rand_num > 50 && rand_num <= 100 && character->get_target_distance_x() <= MIN_DASH_ATTACK_DISTANCE)
			own_state_machine->switch_to("squat");
	}
}

void HornetRunState::on_exit()
{
	character_run_animtaion_left.reset();
	character_run_animtaion_right.reset();
	AudioManager::GetInstance().StopSound(run_sound);
}
/***************************************************************************************/


/**************************** 有关角色掉落状态 ****************************************/
HornetFallState::HornetFallState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_fall_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_fall_right"));
	character_fall_animtaion_right.set_loop(true);
	character_fall_animtaion_right.set_interval(100);

	character_fall_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_fall_left"));
	character_fall_animtaion_left.set_loop(true);
	character_fall_animtaion_left.set_interval(100);

}

void HornetFallState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &character_fall_animtaion_right : &character_fall_animtaion_left);

	//printf("Hornet当前状态：Fall\n");
}

void HornetFallState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character->get_hp() <= 0)						// 角色死亡
	{
		own_state_machine->switch_to("dead");
	}
	else if (character->get_on_ground())
	{
		own_state_machine->switch_to("idle");
		return;
	}

}

void HornetFallState::on_exit()
{
	character_fall_animtaion_left.reset();
	character_fall_animtaion_right.reset();
}
/***************************************************************************************/


/**************************** 有关角色跳跃状态 ****************************************/
HornetJumpState::HornetJumpState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_jump_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_jump_right"));
	character_jump_animtaion_right.set_loop(false);
	character_jump_animtaion_right.set_interval(100);

	character_jump_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_jump_left"));
	character_jump_animtaion_left.set_loop(false);
	character_jump_animtaion_left.set_interval(100);
	
	timer_jump.set_one_shot(true);
	timer_jump.set_wait_time(380.0f);
	timer_jump.set_callback([&]() {
		switch (next_state)
		{
			case STATE_AIM:
			{
				character->set_velocity_y(-1.0f);
				character->set_velocity_x(character->get_is_face_rigth() ? 0.1f : -0.1f);
				break;
			}
			case STATE_ATTACK_SILK:
			{
				character->set_velocity_y(-0.6f);
				character->set_velocity_x(character->get_is_face_rigth() ? 0.2f : -0.2f);
				break;
			}
			case STATE_FALL:
			{
				character->set_velocity_y(-0.8f);
				character->set_velocity_x(character->get_is_face_rigth() ? 0.4f : -0.4f);
				break;
			}
		}
		is_jumping = true;
		});

}

void HornetJumpState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &character_jump_animtaion_right : &character_jump_animtaion_left);

	is_jumping = false;

	timer_jump.restart();

	rand_num = rand() % 101; // 0-100

	if (character->get_hp() > HORNET_STAGE2_HP)
	{
		if (rand_num <= 30)
			next_state = STATE_FALL;
		else if (rand_num <= 65)
			next_state = STATE_AIM;
		else if (rand_num <= 100)
			next_state = STATE_ATTACK_SILK;
	}
	else
	{
		if (rand_num <= 25)
			next_state = STATE_FALL;
		else if (rand_num <= 85)
			next_state = STATE_AIM;
		else if (rand_num <= 100)
			next_state = STATE_ATTACK_SILK;
	}


	//printf("Hornet当前状态：Jump\n");
}

void HornetJumpState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	timer_jump.on_update(delta);

	if (character->get_hp() <= 0)						// 角色死亡
	{
		own_state_machine->switch_to("dead");
	}
	else if (character->get_velocity().y > 0 && is_jumping)
	{
		switch (next_state)
		{
		case STATE_AIM:
		{
			own_state_machine->switch_to("aim");
			break;
		}
		case STATE_ATTACK_SILK:
		{
			own_state_machine->switch_to("throw_silk");
			break;
		}
		case STATE_FALL:
		{
			own_state_machine->switch_to("fall");
			break;
		}
		}
	}
	

}

void HornetJumpState::on_exit()
{
	character_jump_animtaion_left.reset();
	character_jump_animtaion_right.reset();
	is_jumping = false;
}

/***************************************************************************************/


/**************************** 有关角色瞄准状态 ****************************************/
HornetAimState::HornetAimState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_aim_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_aim_right"));
	character_aim_animtaion_right.set_loop(false);
	character_aim_animtaion_right.set_interval(75);
	character_aim_animtaion_right.set_on_finished_callback([&]() {
		is_aiming = false;   // 标记为非瞄准状态
		});

	character_aim_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_aim_left"));
	character_aim_animtaion_left.set_loop(false);
	character_aim_animtaion_left.set_interval(75);
	character_aim_animtaion_left.set_on_finished_callback([&]() {
		is_aiming = false;   // 标记为非瞄准状态
		});

	
}

void HornetAimState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;


	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &character_aim_animtaion_right : &character_aim_animtaion_left);

	is_aiming = true;   // 标记为瞄准状态

	character->set_velocity(0,0);
	character->set_floating(true);

	if (character->get_hp() <= HORNET_STAGE2_HP)						
	{
		character_aim_animtaion_right.set_interval(55);
		character_aim_animtaion_left.set_interval(55);
	}

	//printf("Hornet当前状态：Aim\n");
}

void HornetAimState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character)
	{
		int current_frame_index = character->get_current_animation()->get_frame_index();
		character->set_current_animation(character->get_is_face_rigth() ? &character_aim_animtaion_right : &character_aim_animtaion_left);
		character->get_current_animation()->set_frame_index(current_frame_index);
	}

	if (character->get_hp() <= 0)						// 角色死亡
	{
		own_state_machine->switch_to("dead");
	}
	else if (!is_aiming)							//结束瞄准状态后进入空中冲刺状态
	{
		own_state_machine->switch_to("dash_in_air");
	}

}

void HornetAimState::on_exit()
{
	character_aim_animtaion_left.reset();
	character_aim_animtaion_right.reset();
}
/***************************************************************************************/


/**************************** 有关角色下蹲状态 ****************************************/
HornetSquatState::HornetSquatState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_squat_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_squat_right"));
	character_squat_animtaion_right.set_loop(false);
	character_squat_animtaion_right.set_interval(75);
	character_squat_animtaion_right.set_on_finished_callback([&]() {
		is_squatting = false;   // 标记为非下蹲状态
		});

	character_squat_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_squat_left"));
	character_squat_animtaion_left.set_loop(false);
	character_squat_animtaion_left.set_interval(75);
	character_squat_animtaion_left.set_on_finished_callback([&]() {
		is_squatting = false;   // 标记为非下蹲状态
		});

}

void HornetSquatState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &character_squat_animtaion_right : &character_squat_animtaion_left);

	is_squatting = true;   // 标记为下蹲状态

	character->set_velocity_x(0);

	if (character->get_hp() <= HORNET_STAGE2_HP)						// 角色死亡
	{
		character_squat_animtaion_right.set_interval(55);
		character_squat_animtaion_left.set_interval(55);
	}


	//printf("Hornet当前状态：Squat\n");
}

void HornetSquatState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character)
	{
		int current_frame_index = character->get_current_animation()->get_frame_index();
		character->set_current_animation(character->get_is_face_rigth() ? &character_squat_animtaion_right : &character_squat_animtaion_left);
		character->get_current_animation()->set_frame_index(current_frame_index);
	}


	if (character->get_hp() <= 0)						// 角色死亡
	{
		own_state_machine->switch_to("dead");
	}
	else if (!is_squatting)							//结束瞄准状态后进入地面冲刺状态
	{
		own_state_machine->switch_to("dash_on_floor");
	}
}

void HornetSquatState::on_exit()
{
	character_squat_animtaion_left.reset();
	character_squat_animtaion_right.reset();
}
/***************************************************************************************/


/**************************** 有关角色空中冲刺状态 ****************************************/
HornetDashInAirState::HornetDashInAirState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_dash_in_air_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_dash_in_air_right"));
	character_dash_in_air_animtaion_right.set_loop(true);
	character_dash_in_air_animtaion_right.set_interval(100);

	character_dash_in_air_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_dash_in_air_left"));
	character_dash_in_air_animtaion_left.set_loop(true);
	character_dash_in_air_animtaion_left.set_interval(100);

}

void HornetDashInAirState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	character->set_current_animation(character->get_is_face_rigth() ? &character_dash_in_air_animtaion_right : &character_dash_in_air_animtaion_left);
	
	character->attack_dash_start(Hornet::DashType::AIR);

	character->set_is_last_face_right(character->get_is_face_rigth());

	//printf("Hornet当前状态：DashInAir\n");

}

void HornetDashInAirState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character->get_hp() <= 0)						// 角色死亡
	{
		own_state_machine->switch_to("dead");
	}
	else if (!character->get_is_dashing())
	{
		if(character->get_on_ground())
			own_state_machine->switch_to("hand_land");
		else
			own_state_machine->switch_to("fall");
	}
}

void HornetDashInAirState::on_exit()
{
	character_dash_in_air_animtaion_left.reset();
	character_dash_in_air_animtaion_right.reset();
}
/***************************************************************************************/


/**************************** 有关角色地面冲刺状态 ****************************************/
HornetDashOnGroundState::HornetDashOnGroundState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_dash_on_ground_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_dash_on_floor_right"));
	character_dash_on_ground_animtaion_right.set_loop(true);
	character_dash_on_ground_animtaion_right.set_interval(100);

	character_dash_on_ground_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_dash_on_floor_left"));
	character_dash_on_ground_animtaion_left.set_loop(true);
	character_dash_on_ground_animtaion_left.set_interval(100);

	//添加冲刺攻击计时器
	timer_dash_on_floor.set_wait_time(300);
	timer_dash_on_floor.set_one_shot(true);
	timer_dash_on_floor.set_callback([&]() {
		if (!character)
			return;
		character->attack_dash_end(Hornet::DashType::GROUND);
		});


}

void HornetDashOnGroundState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;
	if (!character)
		return;

	character->set_current_animation(character->get_is_face_rigth() ? &character_dash_on_ground_animtaion_right : &character_dash_on_ground_animtaion_left);

	character->attack_dash_start(Hornet::DashType::GROUND);

	timer_dash_on_floor.restart();

	//printf("Hornet当前状态：DashOnGround\n");

}

void HornetDashOnGroundState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	timer_dash_on_floor.on_update(delta);

	if (character->get_hp() <= 0)						// 角色死亡
	{
		own_state_machine->switch_to("dead");
	}
	else if (!character->get_is_dashing())
	{
		own_state_machine->switch_to("idle");
	}
}

void HornetDashOnGroundState::on_exit()
{
	character_dash_on_ground_animtaion_left.reset();
	character_dash_on_ground_animtaion_right.reset();
}
/***************************************************************************************/


/**************************** 有关角色扔剑状态 ****************************************/
HornetThrowSwordState::HornetThrowSwordState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_thorw_sword_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_throw_sword_right"));
	character_thorw_sword_animtaion_right.set_loop(false);
	character_thorw_sword_animtaion_right.set_interval(75);
	character_thorw_sword_animtaion_right.set_on_finished_callback([&]() {
		is_throwing_sword = false;   // 标记为非扔剑状态
		});
	character_thorw_sword_animtaion_right.add_frame_event(10, [&]() {
		character->throw_sword();
		is_lock_target = false;
		});

	character_thorw_sword_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_throw_sword_left"));
	character_thorw_sword_animtaion_left.set_loop(false);
	character_thorw_sword_animtaion_left.set_interval(75);
	character_thorw_sword_animtaion_left.set_on_finished_callback([&]() {
		is_throwing_sword = false;   // 标记为非扔剑状态
		});
	character_thorw_sword_animtaion_left.add_frame_event(10, [&]() {
		character->throw_sword();
		is_lock_target = false;
		});
}

void HornetThrowSwordState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &character_thorw_sword_animtaion_right : &character_thorw_sword_animtaion_left);

	is_throwing_sword = true;   // 标记为扔剑状态

	is_lock_target = true;

	//printf("Hornet当前状态：ThrowSword\n");

}

void HornetThrowSwordState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character && is_lock_target)
	{
		int current_frame_index = character->get_current_animation()->get_frame_index();
		character->set_current_animation(character->get_is_face_rigth() ? &character_thorw_sword_animtaion_right : &character_thorw_sword_animtaion_left);
		character->get_current_animation()->set_frame_index(current_frame_index);
	}


	if (character->get_hp() <= 0)						// 角色死亡
	{
		own_state_machine->switch_to("dead");
	}
	else if (!is_throwing_sword)
	{
		own_state_machine->switch_to("idle");
	}


}

void HornetThrowSwordState::on_exit()
{
	character_thorw_sword_animtaion_left.reset();
	character_thorw_sword_animtaion_right.reset();
}
/***************************************************************************************/


/**************************** 有关角色扔丝线状态 ****************************************/
HornetThrowSilkState::HornetThrowSilkState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_thorw_silk_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_throw_silk_right"));
	character_thorw_silk_animtaion_right.set_loop(false);
	character_thorw_silk_animtaion_right.set_interval(75);
	character_thorw_silk_animtaion_right.set_on_finished_callback([&]() {
		is_throwing_silk = false;   // 标记为非扔丝线状态
		});
	character_thorw_silk_animtaion_right.add_frame_event(6, [&]() {
		character->attack_silk();
		});


	character_thorw_silk_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_throw_silk_left"));
	character_thorw_silk_animtaion_left.set_loop(false);
	character_thorw_silk_animtaion_left.set_interval(75);
	character_thorw_silk_animtaion_left.set_on_finished_callback([&]() {
		is_throwing_silk = false;   // 标记为非扔丝线状态
		});
	character_thorw_silk_animtaion_left.add_frame_event(6, [&]() {
		character->attack_silk();
		});

}

void HornetThrowSilkState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	character->set_current_animation(character->get_is_face_rigth() ? &character_thorw_silk_animtaion_right : &character_thorw_silk_animtaion_left);

	is_throwing_silk = true;   // 标记为扔丝线状态

	character->set_velocity_x(0);

	if(!character->get_on_ground())
		character->set_floating(true);

	//character->attack_silk();

	//printf("Hornet当前状态：ThrowSilk\n");
}

void HornetThrowSilkState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character->get_hp() <= 0)						// 角色死亡
	{
		own_state_machine->switch_to("dead");
	}
	else if (!is_throwing_silk)
	{
		if (!character->get_on_ground())
		{
			character->set_floating(false);
			own_state_machine->switch_to("fall");
		}
		else
			own_state_machine->switch_to("idle");
		
		
	}
}

void HornetThrowSilkState::on_exit()
{
	character_thorw_silk_animtaion_left.reset();
	character_thorw_silk_animtaion_right.reset();
	is_throwing_silk = false;	
}
/***************************************************************************************/


/**************************** 有关角色扔刺球状态 ****************************************/
HornetThrowBarbState::HornetThrowBarbState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_thorw_barb_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_throw_barb_right"));
	character_thorw_barb_animtaion_right.set_loop(false);
	character_thorw_barb_animtaion_right.set_interval(100);
	character_thorw_barb_animtaion_right.set_on_finished_callback([&]() {
		is_throwing_barb = false;   // 标记为非扔丝线状态
		});
	character_thorw_barb_animtaion_right.add_frame_event(5, [&]() {
		character->generate_barbs();
		});


	character_thorw_barb_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_throw_barb_left"));
	character_thorw_barb_animtaion_left.set_loop(false);
	character_thorw_barb_animtaion_left.set_interval(100);
	character_thorw_barb_animtaion_left.set_on_finished_callback([&]() {
		is_throwing_barb = false;   // 标记为非扔丝线状态
		});
	character_thorw_barb_animtaion_left.add_frame_event(5, [&]() {
		character->generate_barbs();
		});

}

void HornetThrowBarbState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &character_thorw_barb_animtaion_right : &character_thorw_barb_animtaion_left);

	is_throwing_barb = true;   // 标记为扔刺球状态
	
	//printf("Hornet当前状态：ThrowBarb\n");

}

void HornetThrowBarbState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;


	if (character->get_hp() <= 0)						// 角色死亡
	{
		own_state_machine->switch_to("dead");
	}
	else if (!is_throwing_barb)
	{
		own_state_machine->switch_to("idle");
	}

}

void HornetThrowBarbState::on_exit()
{
	character_thorw_barb_animtaion_left.reset();
	character_thorw_barb_animtaion_right.reset();
	is_throwing_barb = false;
}
/***************************************************************************************/


/**************************** 有关角色落地状态 ****************************************/
HornetHandLandState::HornetHandLandState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_hand_land_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_hand_land_right"));
	character_hand_land_animtaion_right.set_loop(false);
	character_hand_land_animtaion_right.set_interval(75);
	character_hand_land_animtaion_right.set_on_finished_callback([&]() {
		is_hand_landing = false;   // 标记为非扔丝线状态
		});

	character_hand_land_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_hand_land_left"));
	character_hand_land_animtaion_left.set_loop(false);
	character_hand_land_animtaion_left.set_interval(75);
	character_hand_land_animtaion_left.set_on_finished_callback([&]() {
		is_hand_landing = false;   // 标记为非扔丝线状态
		});

}

void HornetHandLandState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_last_face_right() ? &character_hand_land_animtaion_right : &character_hand_land_animtaion_left);

	is_hand_landing = true;   // 标记为落地状态

	//printf("Hornet当前状态：HandLand\n");
}

void HornetHandLandState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if(!is_hand_landing)
		own_state_machine->switch_to("idle");


}

void HornetHandLandState::on_exit()
{
	character_hand_land_animtaion_left.reset();
	character_hand_land_animtaion_right.reset();
}
/***************************************************************************************/


/**************************** 有关角色死亡状态 ****************************************/
HornetDeadState::HornetDeadState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	character_dead_animtaion_right.add_animation(resources_manager.find_atlas("atlas_Hornet_idle_right"));
	character_dead_animtaion_right.set_loop(false);
	character_dead_animtaion_right.set_interval(100);

	character_dead_animtaion_left.add_animation(resources_manager.find_atlas("atlas_Hornet_idle_left"));
	character_dead_animtaion_left.set_loop(false);
	character_dead_animtaion_left.set_interval(100);

}

void HornetDeadState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Hornet*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &character_dead_animtaion_right : &character_dead_animtaion_left);

	character->set_velocity_x(0);

	Player* player = dynamic_cast<Player*>(character->get_target());;
	if (player)
	{
		player->set_is_invincible_now(true);
		player->set_is_move_lock(true);
		player->set_velocity_x(0);
		player->get_wd_player()->setTips(_T("很好，这样能行！"));
	}


//	printf("Hornet当前状态：Dead\n");
}

void HornetDeadState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;




}

void HornetDeadState::on_exit()
{
	character_dead_animtaion_left.reset();
	character_dead_animtaion_right.reset();
}
/***************************************************************************************/





