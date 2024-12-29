#pragma once

#include <functional>

using namespace std;

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	inline void restart();

	inline void set_wait_time(float value);

	inline void set_one_shot(bool flag);

	inline void set_callback(function<void()> callback);

	inline void pause();

	inline void resume();

	inline void on_update(float delta);

private:
	float pass_time = 0;				//已经过去的时间
	float wait_time = 0;				//等待时间
	bool paused = false;			//是否暂停
	bool shotted = false;			//是否触发
	bool ont_shot = false;			//是否为单次触发
	function<void()> callback;		//触发回调

};


//重置定时器
void Timer::restart()
{
	pass_time = 0;
	shotted = false;
}

//设置等待时间
void Timer::set_wait_time(float value)
{
	wait_time = value;
}

//设置是否为单次触发
void Timer::set_one_shot(bool flag)
{
	ont_shot = flag;
}

//设置回调函数
void Timer::set_callback(function<void()> callback)
{
	this->callback = callback;
}

//暂停定时器
void Timer::pause()
{
	paused = true;
}

//恢复定时器
void Timer::resume()
{
	paused = false;
}


void Timer::on_update(float delta)
{
	if (paused)
		return;
	pass_time += delta;
	if (pass_time > wait_time)
	{
		if ((!ont_shot || (ont_shot && !shotted)) && callback)
			callback();
		shotted = true;
		pass_time = 0;
	}
}



