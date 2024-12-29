/*
*   �ն���ʿ -C++��Ŀ
*
*/

#pragma comment (lib,"winmm.lib") 
#pragma comment (lib,"Msimg32.lib") 

#include <graphics.h>								 //C++��Easyxͼ�ο⣬��Ҫ��װ
#include <chrono>
#include <thread>
#include <memory>
#include "Parameter/GlobeGameParameters.h"
#include "Game/SceneManager.h"
#include "Utils/helper.h"
#include "Game/MainMenuScene.h"
#include "Game/TestScene.h"
#include "Game/Level1.h"
#include "Game/ResourcesManager.h"
#include "Game/ControllerManager.h"
#include "Game/TimerManager.h"
#include "Game/JsonData.h"
#include "Game/AudioManager.h"

/*
#include "Game/SelectScene.h"
#include "Game/Level1Scene.h"
#include "Game/Scene.h"
#include "Game/Camera.h"
*/


//���������ռ�
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

//������Ϣ
ExMessage msg;
HWND hwnd;



//��������
bool InitGame();


bool InitGame()
{
	hwnd = initgraph(WIN_WIDTH, WIN_HEIGHT);		//��������
	//hwnd = initgraph(WIN_WIDTH, WIN_HEIGHT, EW_SHOWCONSOLE);		//�������ڣ���ʾ����̨

	try
	{
		ResourcesManager::GetInstance().loadAndValidate("res/data/resouces.csv");
	}
	catch (const std::runtime_error& e)
	{
		MessageBoxA(hwnd, e.what(), "��Դ����ʧ��", MB_OK | MB_ICONERROR);
		return false;
	}

	// ����JsonDataʵ��
	JsonData data;
	// ���Դ�ָ���ļ���ȡ����
	bool success = data.ReadFile("res/data/SettingsData.json");
	if (success) {
		int music_volume = 0;
		int effect_volume = 0;
		if (data.Read("Music", music_volume))
			AudioManager::GetInstance().SetMusicVolume(music_volume);
		if(data.Read("Effect", effect_volume))
			AudioManager::GetInstance().SetEffectVolume(effect_volume);
	}
	else
	{
		data.CreateNewFile("res/data/SettingsData.json");
		data.UpdateData("Music", 100);
		data.UpdateData("Effect", 100);
	}


	ControllerManager::GetInstance().create_player(ControllerManager::PlayerType::Player_1);					//������ҿ�����1
	ControllerManager::GetInstance().update_player_input_mapping(ControllerManager::PlayerType::Player_1);		//�������1������ӳ��


	SceneManager& scene_manger = SceneManager::GetInstance();		//��ȡ����������

	Scene* test_scene = new TestScene();												//�������Գ���
	Scene* menu_scene = new MainMenuScene();											//�������˵�����
	Scene* level1 = new Level1();														//�����ؿ�1

	scene_manger.addSceneToMap(SceneManager::SceneType::Menu, menu_scene);				//�����˵�������ӵ�������������
	scene_manger.addSceneToMap(SceneManager::SceneType::Test, test_scene);				//�����Գ�����ӵ�������������
	scene_manger.addSceneToMap(SceneManager::SceneType::Level1, level1);				//���ؿ�1��ӵ�������������

	//scene_manger.create_main_camera();								//�����������
	//scene_manger.switch_to(SceneManager::SceneType::Test);				//�л������Գ���
	scene_manger.switch_to(SceneManager::SceneType::Menu);				//�л������˵�����
//	scene_manger.switch_to(SceneManager::SceneType::Level1);				//�л����ؿ�1
	
	/*�����������*/
	srand((unsigned int)time(NULL));

	return true;
}


int main(int argc, char** argv) {

	if (!InitGame())					//��ʼ����Ϸ
		return 0;

	SceneManager& scene_manger = SceneManager::GetInstance();		//��ȡ����������

	BeginBatchDraw();				//��ʼ˫����

	//֡�ʼ�ʱ
	const nanoseconds	frame_duration(1000000000 / GAME_FPS);
	steady_clock::time_point	start_frame;
	steady_clock::time_point	last_frame;
	last_frame = steady_clock::now();		//��¼��ǰʱ��

	while (scene_manger.getGameStatus()) 
	{
		//����û���������
		while (peekmessage(&msg))
		{
			scene_manger.on_input(msg);
		}

		/* ��¼��ǰʱ�䲢���м������ */
		start_frame = steady_clock::now();
		duration<float>	delta = duration<float>(start_frame - last_frame);

		TimerManager::GetInstance().on_update(delta.count());				//ʱ���������ʱ�䵥λΪ����
		scene_manger.on_update();											//������Ϸ����

		cleardevice();						//�����Ļ

		scene_manger.on_draw();				//��Ⱦͼ��

		FlushBatchDraw();					//������д����Ļ

		//ǿ����֡����֤����
		last_frame = start_frame;
		nanoseconds	sleep_duration = frame_duration - (steady_clock::now() - start_frame);
		if (sleep_duration > nanoseconds(0))
			sleep_for(sleep_duration);

	}

	EndBatchDraw();					//����˫����
	closegraph();					// �ر�ͼ�δ���
	return 0;
}