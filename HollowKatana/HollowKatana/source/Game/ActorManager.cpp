#include "ActorManager.h"
#include "ActorObject.h"
#include "Pawn.h"
#include "Charactor.h"

void ActorManager::add_actor_to_list(ActorObject* object)
{
	actors_list_temp.push_back(object);
}


void ActorManager::destory_actor(ActorObject* object)
{
	if(!object)
		return;
	object->set_is_clear();
}


void ActorManager::remove_actor(ActorObject* object)
{
	actors_list.erase(std::remove(actors_list.begin(), actors_list.end(), object), actors_list.end());
}


void ActorManager::clear_actors()
{
	for (auto it = actors_list.begin(); it != actors_list.end(); ++it) {
		// �� actors_list �е�ÿ��Ԫ�ؽ��в���		
		ActorObject* actor_ptr = *it;
		//destory_item(item_ptr);
		if (actor_ptr)
		{
			actor_ptr->set_is_clear();
		}
	}
//	actors_list.clear();
}


void ActorManager::on_update(float delta)
{
	// �Ƚ� actors_list_temp �е�Ԫ����ӵ� actors_list ��
	for (auto it = actors_list_temp.begin(); it != actors_list_temp.end(); ++it)
	{
		ActorObject* actor_ptr = *it;
		actors_list.push_back(actor_ptr);
	}
	actors_list_temp.clear();

	// ���� actors_list �е�Ԫ�أ�������״̬
	for (auto it = actors_list.begin(); it != actors_list.end(); ++it) {
		// �� actors_list �е�ÿ��Ԫ�ؽ��в���		
		ActorObject* actor_ptr = *it;
		if (actor_ptr)
		{
			if (!actor_ptr->is_clear)
				actor_ptr->on_update(delta);
			else
				remove_list.push_back(actor_ptr);
		}
		else
			remove_list.push_back(actor_ptr);
	}

	// ���� remove_list �е�Ԫ�أ�ɾ�����Ӧ�� ActorObject ����
	for (auto it = remove_list.begin(); it != remove_list.end(); ++it) {
		// �� items_list �е�ÿ��Ԫ�ؽ��в���		
		ActorObject* item_ptr = *it;
		remove_actor(item_ptr);
		if (!item_ptr)
			continue;
		delete item_ptr;
	}
	remove_list.clear(); // ��� remove_list

}
