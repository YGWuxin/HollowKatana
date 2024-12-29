#include "SceneManager.h"
#include "ControllerManager.h"
#include "RenderManager.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "ActorManager.h"
#include "ParticleManager.h"
#include "WidgetManager.h"
#include "TimerManager.h"

void SceneManager::switch_to(SceneType type)
{
	//清除所有可销毁的渲染对象
	RenderManager& render_manger = RenderManager::getInstance();
	render_manger.clearDestroyedItems();

	ActorManager& actor_manger = ActorManager::GetInstance();
	actor_manger.clear_actors();

	WidgetManager& widget_manger = WidgetManager::GetInstance();
	widget_manger.clearAllWidgets();

	Scene* temp = getScene(type);
	if (temp == nullptr)
		return;
	if (current_scene != nullptr)
		current_scene->on_exit();
	current_scene = temp;
	current_scene->on_enter();
}


Scene* SceneManager::getScene(SceneType type)
{
    auto it = SceneMap.find(type);
    if (it != SceneMap.end()) {
        return it->second; // 使用 it->second 获取 Scene*
    }
    return nullptr; // 如果找不到，返回 nullptr
}

void SceneManager::on_update()
{
	if (!main_camera || current_scene == nullptr || !TimerManager::GetInstance().is_valid_frame())
		return;

	float real_time = TimerManager::GetInstance().get_real_time();
	float game_time = TimerManager::GetInstance().get_game_time();

	//如果delta为0，说明是暂停状态，不进行更新
	if(real_time == 0 || game_time == 0)
		return;

	main_camera->on_update(game_time);

	//更新Actor管理器里的物品数据
	ActorManager::GetInstance().on_update(game_time);

	//更新控制器管理器里的控制器数据
	ControllerManager::GetInstance().on_update(game_time);

	//更新控件管理器里的控件数据，不受时间膨胀影响
	WidgetManager::GetInstance().on_update(real_time);

	//粒子管理器更新
	ParticleManager::getInstance().on_update(game_time);

	//检查碰撞，不受时间膨胀影响
	CollisionManager::GetInstance().process_collide(real_time);

	//更新当前场景的数据
	current_scene->on_update(game_time);

	//记录当前帧的碰撞箱的位置，需要放在更新游戏数据之后
	CollisionManager::GetInstance().record_last_position();

}


void SceneManager::on_draw()
{
	if (!main_camera)
		return;
	RenderManager& render_manager = RenderManager::getInstance();
	CollisionManager& collision_manger = CollisionManager::GetInstance();
	WidgetManager& widget_manger = WidgetManager::GetInstance();

	render_manager.render_object(*main_camera);

	widget_manger.on_draw();

	collision_manger.on_debug_render(*main_camera);
}


void SceneManager::on_input(const ExMessage& msg)
{
	if (!main_camera)
		return;
	//检查玩家的输入
	ControllerManager::GetInstance().on_input(msg);
	WidgetManager::GetInstance().handleInputEvent(msg);
	if (current_scene == nullptr)
		return;
	current_scene->on_input(msg);
}

void SceneManager::addSceneToMap(SceneType type, Scene* scene)
{
	if (scene != nullptr) {
		auto result = SceneMap.find(type);
		if (result == SceneMap.end()) {
			// 键不存在，插入新的键值对
			SceneMap.insert(std::pair<SceneType, Scene*>(type, scene));
		}
		else {
			// 键已存在，执行更新操作或其他处理
			result->second = scene; // 更新现有的 Scene* 指针
			// 或者其他处理逻辑
		}
	}
}

void SceneManager::removeSceneFromMap(SceneType type)
{
	auto it = SceneMap.find(type);
	if (it != SceneMap.end()) {
		// 键存在，删除对应的键值对
		SceneMap.erase(it);
	}
}

