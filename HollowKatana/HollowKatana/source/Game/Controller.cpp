#include "Controller.h"
#include "Pawn.h"
#include "ActorManager.h"

void Controller::Possess(Pawn* Pawn)
{
	if (!Pawn)
		return;
	UnPossess(false);
	Pawn->set_own_controller(this);
	Pawn->on_Possess();
	ControlledPawn = Pawn;
}

void Controller::UnPossess(bool isDestroy)
{
	if (!ControlledPawn)
		return;
	ControlledPawn->on_UnPossess();
	ControlledPawn->set_own_controller(nullptr);
	if (isDestroy)
		ActorManager::GetInstance().destory_actor(ControlledPawn);
	ControlledPawn = nullptr;
	//printf("UnPossess");
}

