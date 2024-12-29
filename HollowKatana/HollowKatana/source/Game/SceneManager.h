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
        static SceneManager instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
	
    enum class SceneType
    {
        Test,
        Menu,
        Level1,
    };

    //�л�����
    void switch_to(SceneType type);

    //���µ�ǰ������Ϸ����
    void on_update();

    //��Ⱦ��ǰ����
    void on_draw();

    //��⵱ǰ�����������״̬
    void on_input(const ExMessage& msg);

    //��ӳ���
    void addSceneToMap(SceneType type, Scene* scene);

    //�Ƴ�����
    void removeSceneFromMap(SceneType type);

    //��ȡ����
    Scene* getScene(SceneType type);

    //�����������
    void set_main_camera(Camera* camera) { main_camera = camera; }

    //��ȡ������� 
    Camera* get_main_camera() { return main_camera; }


    bool getGameStatus() { return isGameRuning; }

    void QuitGame() { isGameRuning = false; }

private:
    SceneManager() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~SceneManager() = default;   // ˽��������������ֹ�ⲿ����ʵ��

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

