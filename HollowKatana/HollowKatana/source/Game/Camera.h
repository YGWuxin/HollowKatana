#pragma once

#include "Vector2.h"
#include "../Utils/Timer.h"


class Camera
{
public:
	Camera();
	~Camera() = default;

	const Vector2& get_position() const
	{
		return position;
	}

	void set_posistion(Vector2& current_position) 
	{
		this->position = current_position;
		this->temp_position = this->position;
	}

	void set_posistion_x(float posistion_x)
	{
		this->position.x = posistion_x;
		this->temp_position = this->position;
	}
	
	void set_posistion_y(float posistion_y)
	{
		this->position.y = posistion_y;
		this->temp_position = this->position;
	}

	void reset();

	void on_update(int delta);

	void Shake(float strenth, float duration,float frq = 0, int shake_priority = 0);

private:
	Vector2 position = Vector2(0, 0);		//摄像机位置
	Vector2 temp_position = Vector2(0, 0);
	Timer timer_shake;
	bool is_shakeing = false;
	float shakeing_strength = 0;
	float frq = 2.0f;
	float frq_temp = 0;
	int shake_priority = -1;					//震动优先级


};

