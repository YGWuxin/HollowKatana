#pragma once

#include <graphics.h>
#include "Camera.h"


//场景基类
class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	virtual void on_enter() {};							//场景加载函数
	virtual void on_update(int delta) { };				//场景中游戏数据更新函数
	virtual void on_input(const ExMessage &msg) {};		//用户输入函数
	virtual void on_exit() {};							//场景卸载函数

private:

protected:
	Camera default_camera;								//默认摄像机

};





