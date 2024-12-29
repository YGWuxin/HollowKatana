#pragma once
#include "Particle.h"


class DashInAirEffect : public Particle
{
public:
	DashInAirEffect(Vector2 position, bool is_right, int lifespan);
	~DashInAirEffect() = default;

};


class DashOnFloorEffect : public Particle
{
public:
	DashOnFloorEffect(Vector2 position, bool is_right, int lifespan);
	~DashOnFloorEffect() = default;

};
