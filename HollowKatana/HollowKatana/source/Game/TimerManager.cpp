#include "TimerManager.h"
#include <cmath>
#include <cstdio>

void TimerManager::on_update(float delta)
{
    real_time = delta * 1000.0f;					//µ¥Î»ÎªºÁÃë
    game_time = real_time * time_dilation;
}


void TimerManager::lerp_float(float& current_value, float target_value, float speed, TimerType timer_type)
{
    if (target_value == current_value || speed == 0.0f) return;
    float time = (timer_type == TimerType::RealTime) ? real_time : game_time;
    const float epsilon = 0.001f;

    float value_diff = target_value - current_value;
    float value_diff_abs = std::abs(value_diff);


    if (value_diff > 0.0f)
        current_value += value_diff_abs * speed * time / 1000.0f;
    else
        current_value -= value_diff_abs * speed * time / 1000.0f;

    if (value_diff_abs <= epsilon)
        current_value = target_value;
}

void TimerManager::lerp_float(float& current_value, float target_value, float speed, float delta)
{
    if(target_value == current_value || speed == 0.0f) return;
    const float epsilon = 0.001f;
    float value_diff = target_value - current_value;
    float value_diff_abs = std::abs(value_diff);

    if (value_diff > 0.0f)
        current_value += value_diff_abs * speed * delta / 1000.0f;
    else
        current_value -= value_diff_abs * speed * delta / 1000.0f;

    if (value_diff_abs <= epsilon)
        current_value = target_value;
}


void TimerManager::lerp_float(float& current_value, float start_value, float end_value, float speed, float delta)
{
    if (end_value == current_value || speed == 0.0f) return;
    float value_diff = end_value - start_value;
        
    if (value_diff > 0.0f)
    {
        current_value += speed * delta / 1000.0f;
        if(current_value >= end_value)
            current_value = end_value;
    }
    else
    {
        current_value -= speed * delta / 1000.0f;
        if (current_value <= end_value)
            current_value = end_value;
    }


}


void TimerManager::lerp_float(float& current_value, float start_value, float end_value, float speed, TimerType timer_type)
{
    if (end_value == current_value || speed == 0.0f) return;
    float time = (timer_type == TimerType::RealTime) ? real_time : game_time;
    float value_diff = end_value - start_value;

    if (value_diff > 0.0f)
    {
        current_value += speed * time / 1000.0f;
        if (current_value >= end_value)
            current_value = end_value;
    }
    else
    {
        current_value -= speed * time / 1000.0f;
        if (current_value <= end_value)
            current_value = end_value;
    }
}


