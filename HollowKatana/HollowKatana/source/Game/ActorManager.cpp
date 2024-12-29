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
		// 对 actors_list 中的每个元素进行操作		
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
	// 先将 actors_list_temp 中的元素添加到 actors_list 中
	for (auto it = actors_list_temp.begin(); it != actors_list_temp.end(); ++it)
	{
		ActorObject* actor_ptr = *it;
		actors_list.push_back(actor_ptr);
	}
	actors_list_temp.clear();

	// 遍历 actors_list 中的元素，更新其状态
	for (auto it = actors_list.begin(); it != actors_list.end(); ++it) {
		// 对 actors_list 中的每个元素进行操作		
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

	// 遍历 remove_list 中的元素，删除其对应的 ActorObject 对象
	for (auto it = remove_list.begin(); it != remove_list.end(); ++it) {
		// 对 items_list 中的每个元素进行操作		
		ActorObject* item_ptr = *it;
		remove_actor(item_ptr);
		if (!item_ptr)
			continue;
		delete item_ptr;
	}
	remove_list.clear(); // 清空 remove_list

}
