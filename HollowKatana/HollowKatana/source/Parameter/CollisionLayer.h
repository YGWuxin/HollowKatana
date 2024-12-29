#pragma once

#include "../Parameter/GlobeGameParameters.h"


enum class CollisionLayer
{
	None = 0,
	Player = BIT0,
	PlatformSmall = BIT1,
	PlatformLarge = BIT2,
	Bullet = BIT3,
	Eenemy = BIT4,
	AirWall = BIT5,
	PlayerAttack = BIT6,
	EnemyAttack = BIT7,
	EnemyProjectile = BIT8,
};



