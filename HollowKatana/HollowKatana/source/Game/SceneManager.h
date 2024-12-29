#pragma once

#include <map>
#include <utility> 
#include <graphics.h>	
#include "Scene.h"
#include "../Utils/Timer.h"

class Camera;

class SceneManager
{
public:
    static SceneManager& GetInstance()
    {
        static SceneManager instance; // 静态局部变量，确保唯一性
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
	
    enum class SceneType
    {
        Test,
        Menu,
        Level1,
    };

    //切换场景
    void switch_to(SceneType type);

    //更新当前场景游戏数据
    void on_update();

    //渲染当前场景
    void on_draw();

    //检测当前场景玩家输入状态
    void on_input(const ExMessage& msg);

    //添加场景
    void addSceneToMap(SceneType type, Scene* scene);

    //移除场景
    void removeSceneFromMap(SceneType type);

    //获取场景
    Scene* getScene(SceneType type);

    //设置主摄像机
    void set_main_camera(Camera* camera) { main_camera = camera; }

    //获取主摄像机 
    Camera* get_main_camera() { return main_camera; }


    bool getGameStatus() { return isGameRuning; }

    void QuitGame() { isGameRuning = false; }

private:
    SceneManager() = default;    // 私有构造函数，防止外部创建实例
    ~SceneManager() = default;   // 私有析构函数，防止外部销毁实例

private:
    Timer timer_frame;
    int farme = 0;
    Scene* current_scene = nullptr;
    std::map<SceneType, Scene*> SceneMap;
    Camera* main_camera = nullptr;

    bool isGameRuning = true;
    float last_delta = 0.0f;

    bool is_last_delta = false;


public:
    const char* menu_bgm = nullptr;

};

