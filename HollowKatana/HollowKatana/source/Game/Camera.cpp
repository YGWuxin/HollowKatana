#include "Camera.h"

Camera::Camera()
{
	timer_shake.set_one_shot(true);
	timer_shake.set_callback([&]() {
		is_shakeing = false;
		this->position = this->temp_position;
		shake_priority = -1;
		});
}

void Camera::reset()
{
	this->position = { 0,0 };
}

void Camera::Shake(float strenth, float duration, float frq, int shake_priority)
{
	if (shake_priority <= this->shake_priority)
		return;
	this->shake_priority = shake_priority;
	this->position = this->temp_position;
	is_shakeing = true;
	this->frq = frq;
	frq_temp = 0;
	shakeing_strength = strenth;
	timer_shake.set_wait_time(duration);
	timer_shake.restart();
	//printf("start_shakeing\r\n");
}


void Camera::on_update(int delta)
{
	timer_shake.on_update(delta);
	if (is_shakeing && (frq_temp >= frq))
	{
		position.x = (-50 + rand() % 100) / 50.0f * shakeing_strength;
		position.y = (-50 + rand() % 100) / 50.0f * shakeing_strength;
		frq_temp = 0;
		//printf("shakeing\r\n");
	}
	frq_temp += delta;

}
