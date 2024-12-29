#pragma once
#include "ActorObject.h"

class ActorManager;
class Animation;

class Sword : public ActorObject
{
	friend class ActorManager;

protected:
	Sword(Vector2 position,bool move_right);

	virtual ~Sword();

	void on_update(float delta) override;

	void handleCollision(const HitInfo& hit_info) override;


private:
	Animation* animation;

	const float speed = 1.25f;

};

