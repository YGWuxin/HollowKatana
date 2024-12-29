#include "HornetEffect.h"
#include "ResourcesManager.h"
#include "atlas.h"


DashInAirEffect::DashInAirEffect(Vector2 position, bool is_right, int lifespan) : Particle(position, lifespan)
{
	Atlas* atlas = nullptr;
	if(is_right)
		atlas = ResourcesManager::GetInstance().find_atlas("atlas_Hornet_dash_in_air_vfx_right");
	else
		atlas = ResourcesManager::GetInstance().find_atlas("atlas_Hornet_dash_in_air_vfx_left");

	set_atlas(atlas);
}


DashOnFloorEffect::DashOnFloorEffect(Vector2 position, bool is_right, int lifespan) : Particle(position, lifespan)
{
	Atlas* atlas = nullptr;
	if (is_right)
		atlas = ResourcesManager::GetInstance().find_atlas("atlas_Hornet_dash_on_floor_vfx_right");
	else
		atlas = ResourcesManager::GetInstance().find_atlas("atlas_Hornet_dash_on_floor_vfx_left");

	set_atlas(atlas);
}


