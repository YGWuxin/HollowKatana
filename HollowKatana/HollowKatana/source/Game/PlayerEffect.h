#pragma once
#include "Particle.h"


class JumpEffect : public Particle
{

public:
	JumpEffect(Vector2 position, int lifespan);
	~JumpEffect() = default;

};


class LandEffect : public Particle
{

public:
	LandEffect(Vector2 position, int lifespan);
	~LandEffect() = default;
};


class AttackEffect : public Particle
{
public:
	enum AttackDirection
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

public:
	AttackEffect(Vector2 position, int lifespan, AttackDirection direction);
	~AttackEffect() = default;
};

