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
	//������п����ٵ���Ⱦ����
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
        return it->second; // ʹ�� it->second ��ȡ Scene*
    }
    return nullptr; // ����Ҳ��������� nullptr
}

void SceneManager::on_update()
{
	if (!main_camera || current_scene == nullptr || !TimerManager::GetInstance().is_valid_frame())
		return;

	float real_time = TimerManager::GetInstance().get_real_time();
	float game_time = TimerManager::GetInstance().get_game_time();

	//���deltaΪ0��˵������ͣ״̬�������и���
	if(real_time == 0 || game_time == 0)
		return;

	main_camera->on_update(game_time);

	//����Actor�����������Ʒ����
	ActorManager::GetInstance().on_update(game_time);

	//���¿�������������Ŀ���������
	ControllerManager::GetInstance().on_update(game_time);

	//���¿ؼ���������Ŀؼ����ݣ�����ʱ������Ӱ��
	WidgetManager::GetInstance().on_update(real_time);

	//���ӹ���������
	ParticleManager::getInstance().on_update(game_time);

	//�����ײ������ʱ������Ӱ��
	CollisionManager::GetInstance().process_collide(real_time);

	//���µ�ǰ����������
	current_scene->on_update(game_time);

	//��¼��ǰ֡����ײ���λ�ã���Ҫ���ڸ�����Ϸ����֮��
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
	//�����ҵ�����
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
			// �������ڣ������µļ�ֵ��
			SceneMap.insert(std::pair<SceneType, Scene*>(type, scene));
		}
		else {
			// ���Ѵ��ڣ�ִ�и��²�������������
			result->second = scene; // �������е� Scene* ָ��
			// �������������߼�
		}
	}
}

void SceneManager::removeSceneFromMap(SceneType type)
{
	auto it = SceneMap.find(type);
	if (it != SceneMap.end()) {
		// �����ڣ�ɾ����Ӧ�ļ�ֵ��
		SceneMap.erase(it);
	}
}

