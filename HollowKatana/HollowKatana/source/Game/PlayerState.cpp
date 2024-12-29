#include "PlayerState.h"
#include "Player.h"
#include "StateMachine.h"
#include "ResourcesManager.h"
#include "AudioManager.h"
#include "ParticleManager.h"
#include "PlayerEffect.h"
#include  "Vector2.h"
#include "Controller.h"
#include "SceneManager.h"
#include "WD_Player.h"

/* 有关角色默认状态*/
PlayerIdleState::PlayerIdleState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	player_idle_animtaion_right.add_animation(resources_manager.find_image("img_player_idle_right"));
	player_idle_animtaion_right.set_loop(true);
	player_idle_animtaion_right.set_interval(100);

	player_idle_animtaion_left.add_animation(resources_manager.find_image("img_player_idle_left"));
	player_idle_animtaion_left.set_loop(true);
	player_idle_animtaion_left.set_interval(100);

}

void PlayerIdleState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Player*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_idle_animtaion_right : &player_idle_animtaion_left);

}


void PlayerIdleState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_idle_animtaion_right : &player_idle_animtaion_left);

	if (character->get_hp() <= 0)
	{
		own_state_machine->switch_to("dead");
		return;

	}
	if (character->get_is_attacking())
	{
		own_state_machine->switch_to("attack");
		return;
	}
	if (character->get_velocity().y > 0 && !character->get_on_ground())
	{
		own_state_machine->switch_to("fall");
		return;
	}
	if (character->get_velocity().y < 0)
	{
		own_state_machine->switch_to("jump");
		return;
	}
	if (character->is_rolling_now())
	{
		own_state_machine->switch_to("roll");
		return;
	}
	if (character->get_velocity().x != 0)
	{
		own_state_machine->switch_to("run");
		return;
	}
	

}


void PlayerIdleState::on_exit()
{
	player_idle_animtaion_left.reset();
	player_idle_animtaion_right.reset();
}


/* 有关角色奔跑状态*/
PlayerRunState::PlayerRunState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	player_run_animtaion_right.add_animation(resources_manager.find_image("img_player_run_right"));
	player_run_animtaion_right.set_loop(true);
	player_run_animtaion_right.set_interval(70);

	player_run_animtaion_left.add_animation(resources_manager.find_image("img_player_run_left"));
	player_run_animtaion_left.set_loop(true);
	player_run_animtaion_left.set_interval(70);

}

void PlayerRunState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Player*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_run_animtaion_right : &player_run_animtaion_left);

	run_sound = AudioManager::GetInstance().PlaySoundAudio("res/audio/player/player_run.mp3", AudioManager::AudioType::Effect,true);

}


void PlayerRunState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_run_animtaion_right : &player_run_animtaion_left);

	if (character->get_hp() <= 0)
	{
		own_state_machine->switch_to("dead");
		return;
	}
	if (character->get_is_attacking())
	{
		own_state_machine->switch_to("attack");
		return;
	}
	if (character->get_velocity().y > 0 && !character->get_on_ground())
	{
		own_state_machine->switch_to("fall");
		return;
	}
	if (character->get_velocity().y < 0)
	{
		own_state_machine->switch_to("jump");
		return;
	}
	if (character->is_rolling_now())
	{
		own_state_machine->switch_to("roll");
		return;
	}
	if (character->get_velocity().x == 0)
	{
		own_state_machine->switch_to("idle");
		return;
	}
	
}

void PlayerRunState::on_exit()
{
	player_run_animtaion_left.reset();
	player_run_animtaion_left.reset();
	AudioManager::GetInstance().StopSound(run_sound);
}




/* 有关角色跳跃状态*/
PlayerJumpState::PlayerJumpState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	player_jump_animtaion_right.add_animation(resources_manager.find_image("img_player_jump_right"));
	player_jump_animtaion_right.set_loop(true);
	player_jump_animtaion_right.set_interval(100);

	player_jump_animtaion_left.add_animation(resources_manager.find_image("img_player_jump_left"));
	player_jump_animtaion_left.set_loop(true);
	player_jump_animtaion_left.set_interval(100);

}

void PlayerJumpState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Player*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_jump_animtaion_right : &player_jump_animtaion_left);
}


void PlayerJumpState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_jump_animtaion_right : &player_jump_animtaion_left);

	if (character->get_hp() <= 0)
	{
		own_state_machine->switch_to("dead");
		return;
	}
	if (character->get_is_attacking())
	{
		own_state_machine->switch_to("attack");
		return;
	}
	if (character->get_velocity().y > 0 && !character->get_on_ground())
	{
		own_state_machine->switch_to("fall");
		return;
	}
}

void PlayerJumpState::on_exit()
{
	if (!character->get_is_attacking())
	{
		player_jump_animtaion_right.reset();
		player_jump_animtaion_left.reset();
	}
	//AudioManager::GetInstance().StopSound(jump_sound);
}


/* 有关角色下落状态*/
PlayerFallState::PlayerFallState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	player_fall_animtaion_right.add_animation(resources_manager.find_image("img_player_fall_right"));
	player_fall_animtaion_right.set_loop(true);
	player_fall_animtaion_right.set_interval(100);

	player_fall_animtaion_left.add_animation(resources_manager.find_image("img_player_fall_left"));
	player_fall_animtaion_left.set_loop(true);
	player_fall_animtaion_left.set_interval(100);

}

void PlayerFallState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Player*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_fall_animtaion_right : &player_fall_animtaion_left);

}


void PlayerFallState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_fall_animtaion_right : &player_fall_animtaion_left);


	if (character->get_hp() <= 0)
	{
		own_state_machine->switch_to("dead");
		return;
	}
	if (character->get_is_attacking())
	{
		own_state_machine->switch_to("attack");
		return;
	}
	if (character->get_on_ground() && character->get_velocity().x != 0)
	{
		own_state_machine->switch_to("run");
		return;
	}

	if (character->get_on_ground() && character->get_velocity().x == 0)
	{
		own_state_machine->switch_to("idle");
		return;
	}


}

void PlayerFallState::on_exit()
{
	if (character->get_on_ground())
	{
		player_fall_animtaion_right.reset();
		player_fall_animtaion_left.reset();
	}
}



/* 有关角色翻滚状态*/
PlayerRollState::PlayerRollState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	player_roll_animtaion_right.add_animation(resources_manager.find_image("img_player_roll_right"));
	player_roll_animtaion_right.set_loop(true);
	player_roll_animtaion_right.set_interval(60);

	player_roll_animtaion_left.add_animation(resources_manager.find_image("img_player_roll_left"));
	player_roll_animtaion_left.set_loop(true);
	player_roll_animtaion_left.set_interval(60);

}

void PlayerRollState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Player*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_roll_animtaion_right : &player_roll_animtaion_left);

	AudioManager::GetInstance().PlaySoundAudio("res/audio/player/player_roll.mp3", AudioManager::AudioType::Effect, 50);

}


void PlayerRollState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_roll_animtaion_right : &player_roll_animtaion_left);

	if (character->get_hp() <= 0)
	{
		own_state_machine->switch_to("dead");
		return;
	}
	if (!character->is_rolling_now() && character->get_velocity().x != 0)
	{
		own_state_machine->switch_to("run");
		return;
	}

	if (!character->is_rolling_now() && character->get_velocity().x == 0)
	{
		own_state_machine->switch_to("idle");
		return;
	}


}

void PlayerRollState::on_exit()
{
	player_roll_animtaion_right.reset();
	player_roll_animtaion_left.reset();
	//AudioManager::GetInstance().PlaySoundAudio("res/audio/player/player_land.mp3", AudioManager::AudioType::Effect, 50, false);
}



/* 有关角色攻击状态*/
PlayerAttackState::PlayerAttackState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	player_attack_animtaion_right.add_animation(resources_manager.find_image("img_player_attack_right"));
	player_attack_animtaion_right.set_loop(false);
	player_attack_animtaion_right.set_interval(60);
	player_attack_animtaion_right.set_on_finished_callback([&] {
		if (!character)
			return;
		character->set_is_attacking(false);
		});


	player_attack_animtaion_left.add_animation(resources_manager.find_image("img_player_attack_left"));
	player_attack_animtaion_left.set_loop(false);
	player_attack_animtaion_left.set_interval(60);
	player_attack_animtaion_left.set_on_finished_callback([&] {
		if (!character)
			return;
		character->set_is_attacking(false);
		});

}

void PlayerAttackState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Player*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_attack_animtaion_right : &player_attack_animtaion_left);

}


void PlayerAttackState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_attack_animtaion_right : &player_attack_animtaion_left);

	if (character->get_hp() <= 0)
	{
		own_state_machine->switch_to("dead");
		return;
	}
	if (!character->get_is_attacking() && character->get_on_ground())
	{
		if(character->get_velocity().x != 0)
			own_state_machine->switch_to("run");
		else
			own_state_machine->switch_to("idle");
		return;
	}

	if (!character->get_is_attacking() && !character->get_on_ground())
	{
		if (character->get_velocity().x > 0)
			own_state_machine->switch_to("fall");
		else
			own_state_machine->switch_to("jump");
		return;
	}
}

void PlayerAttackState::on_exit()
{
	player_attack_animtaion_right.reset();
	player_attack_animtaion_left.reset();
	//AudioManager::GetInstance().PlaySoundAudio("res/audio/player/player_land.mp3", AudioManager::AudioType::Effect, 50, false);
}





/* 有关角色死亡状态*/
PlayerDeadState::PlayerDeadState()
{
	ResourcesManager& resources_manager = ResourcesManager::GetInstance();
	player_dead_animtaion_right.add_animation(resources_manager.find_image("img_player_dead_right"));
	player_dead_animtaion_right.set_loop(false);
	player_dead_animtaion_right.set_interval(100);
	player_dead_animtaion_right.set_on_finished_callback([&]() {
		//SceneManager::GetInstance().switch_to(SceneManager::SceneType::Menu);
		character->set_is_dead(true);
		
		});


	player_dead_animtaion_left.add_animation(resources_manager.find_image("img_player_dead_left"));
	player_dead_animtaion_left.set_loop(false);
	player_dead_animtaion_left.set_interval(100);
	player_dead_animtaion_left.set_on_finished_callback([&]() {
		//SceneManager::GetInstance().switch_to(SceneManager::SceneType::Menu);
		character->set_is_dead(true);
		});

}

void PlayerDeadState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<Player*>(own_state_machine->get_own_charactor());;

	if (!character)
		return;

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? &player_dead_animtaion_right : &player_dead_animtaion_left);

	AudioManager::GetInstance().PlaySoundAudio("res/audio/player/player_dead.mp3", AudioManager::AudioType::Effect, 50);

	character->set_run_velocity(0);

	//character->set_is_invincible_now(true);

	character->get_wd_player()->setTips(_T("还是....做不到吗?"));

}


void PlayerDeadState::on_update(float delta)
{
	if (!own_state_machine || !character)
		return;



}

void PlayerDeadState::on_exit()
{
	player_dead_animtaion_right.reset();
	player_dead_animtaion_left.reset();
}










