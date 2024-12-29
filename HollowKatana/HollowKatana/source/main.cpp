/*
*   空洞武士 -C++项目
*
*/

#pragma comment (lib,"winmm.lib") 
#pragma comment (lib,"Msimg32.lib") 

#include <graphics.h>								 //C++的Easyx图形库，需要安装
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


//引入命名空间
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

//操作信息
ExMessage msg;
HWND hwnd;



//函数声明
bool InitGame();


bool InitGame()
{
	hwnd = initgraph(WIN_WIDTH, WIN_HEIGHT);		//创建窗口
	//hwnd = initgraph(WIN_WIDTH, WIN_HEIGHT, EW_SHOWCONSOLE);		//创建窗口，显示控制台

	try
	{
		ResourcesManager::GetInstance().loadAndValidate("res/data/resouces.csv");
	}
	catch (const std::runtime_error& e)
	{
		MessageBoxA(hwnd, e.what(), "资源加载失败", MB_OK | MB_ICONERROR);
		return false;
	}

	// 创建JsonData实例
	JsonData data;
	// 尝试从指定文件读取数据
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


	ControllerManager::GetInstance().create_player(ControllerManager::PlayerType::Player_1);					//创建玩家控制器1
	ControllerManager::GetInstance().update_player_input_mapping(ControllerManager::PlayerType::Player_1);		//设置玩家1的输入映射


	SceneManager& scene_manger = SceneManager::GetInstance();		//获取场景管理器

	Scene* test_scene = new TestScene();												//创建测试场景
	Scene* menu_scene = new MainMenuScene();											//创建主菜单场景
	Scene* level1 = new Level1();														//创建关卡1

	scene_manger.addSceneToMap(SceneManager::SceneType::Menu, menu_scene);				//将主菜单场景添加到场景管理器中
	scene_manger.addSceneToMap(SceneManager::SceneType::Test, test_scene);				//将测试场景添加到场景管理器中
	scene_manger.addSceneToMap(SceneManager::SceneType::Level1, level1);				//将关卡1添加到场景管理器中

	//scene_manger.create_main_camera();								//创建主摄像机
	//scene_manger.switch_to(SceneManager::SceneType::Test);				//切换到测试场景
	scene_manger.switch_to(SceneManager::SceneType::Menu);				//切换到主菜单场景
//	scene_manger.switch_to(SceneManager::SceneType::Level1);				//切换到关卡1
	
	/*配置随机种子*/
	srand((unsigned int)time(NULL));

	return true;
}


int main(int argc, char** argv) {

	if (!InitGame())					//初始化游戏
		return 0;

	SceneManager& scene_manger = SceneManager::GetInstance();		//获取场景管理器

	BeginBatchDraw();				//开始双缓冲

	//帧率计时
	const nanoseconds	frame_duration(1000000000 / GAME_FPS);
	steady_clock::time_point	start_frame;
	steady_clock::time_point	last_frame;
	last_frame = steady_clock::now();		//记录当前时间

	while (scene_manger.getGameStatus()) 
	{
		//检查用户按键输入
		while (peekmessage(&msg))
		{
			scene_manger.on_input(msg);
		}

		/* 记录当前时间并进行间隔计算 */
		start_frame = steady_clock::now();
		duration<float>	delta = duration<float>(start_frame - last_frame);

		TimerManager::GetInstance().on_update(delta.count());				//时间管理器，时间单位为毫秒
		scene_manger.on_update();											//更新游戏数据

		cleardevice();						//清空屏幕

		scene_manger.on_draw();				//渲染图形

		FlushBatchDraw();					//将缓冲写入屏幕

		//强制锁帧，保证性能
		last_frame = start_frame;
		nanoseconds	sleep_duration = frame_duration - (steady_clock::now() - start_frame);
		if (sleep_duration > nanoseconds(0))
			sleep_for(sleep_duration);

	}

	EndBatchDraw();					//结束双缓冲
	closegraph();					// 关闭图形窗口
	return 0;
}