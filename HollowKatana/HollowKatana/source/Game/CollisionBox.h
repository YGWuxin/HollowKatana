#pragma once

#include "Vector2.h"
#include "../Parameter/CollisionLayer.h"
#include "../Parameter/GlobeGameParameters.h"

#include <functional>

class CollisionManager;
class ActorObject;
class CollisionBox;

struct HitInfo
{
	ActorObject* actor = nullptr;
	CollisionBox* box = nullptr;
	float delta = 0;
	Vector2 size = { 0,0 };
	Vector2 position = { 0,0 };
	Vector2 distance = { 0,0 };
	Vector2 normal = { 0,0 };
	CollisionLayer layer = CollisionLayer::None;
};


class CollisionBox 
{
	friend class CollisionManager;

private:
	Vector2 size = {0,0};
	Vector2 position = { 0,0 };
	bool enabled = false;
	std::function<void(HitInfo)> on_collide;
	CollisionLayer layer_self = CollisionLayer::None;		//自身碰撞层级	
	int layer_dst = 0;										//碰撞到的层级
	ActorObject* actor_object = nullptr;

public:
	//设置拥有的物品
	void set_item_object(ActorObject* actor) { actor_object = actor; }

	//获取拥有的物品
	ActorObject* get_item_object() { return actor_object; }

	//设置碰撞箱是否启用
	void set_enabled(bool flag) { enabled = flag; };

	//获取是否启用
	bool get_enabled() { return enabled; };

	//设置碰撞箱大小
	void set_size(Vector2 size) { this->size = size; };

	//获取碰撞箱大小
	Vector2 get_size() { return size; };

	//设置碰撞箱位置
	void set_position(Vector2 position) { this->position = position; };

	//设置碰撞箱位置
	void set_position(Vector2 position, AnchorMode mode)
	{ 
		switch (mode)
		{
		case AnchorMode::Centered:
			this->position = position;
			break;
		case AnchorMode::BottomCrented:
			this->position.x = position.x;
			this->position.y = position.y - this->size.y / 2;
			break;
		default:
			break;
		}
	};

	//设置碰撞箱位置
	void set_position(Vector2 position, AnchorMode mode,int offset_x,int offset_y)
	{
		switch (mode)
		{
		case AnchorMode::Centered:
			this->position.x= position.x + offset_x;
			this->position.y = position.y + offset_y;
			break;
		case AnchorMode::BottomCrented:
			this->position.x = position.x + offset_x;
			this->position.y = (position.y - this->size.y / 2) + offset_y;
			break;
		default:
			break;
		}
	};

	//获取碰撞箱位置
	Vector2 get_position() { return position; };

	//获取碰撞箱位置
	Vector2 get_position(AnchorMode mode)
	{
		switch (mode)
		{
		case AnchorMode::Centered:
			return position;
		case AnchorMode::BottomCrented:
			return { position.x,position.y + size.y / 2 };
		default:
			return position;
		}
	}

	//设置碰撞回调函数
	void set_on_collide(std::function<void(HitInfo)> on_collide) { this->on_collide = on_collide; };

	//设置自身层级
	void set_layer_self(CollisionLayer layer_self) { this->layer_self = layer_self;  };

	//获取自身层级
	CollisionLayer get_layer_self() { return layer_self; };

	//添加需要碰撞到的层级
	void add_layer_dst(CollisionLayer dst) { layer_dst = layer_dst | static_cast<int>(dst); };

	//取除所有需要碰撞的层级
	void remove_layer_all() { layer_dst = 0; }

	//移除碰撞到的层级
	void remove_layer_dst(CollisionLayer dst) { layer_dst = layer_dst & ~static_cast<int>(dst); };

	//获取碰撞到的层级
	int get_layer_dst() { return layer_dst; };

	//设置是否为触发器
	void set_is_trigger(bool flag) { is_trigger = flag; };

	//获取是否为触发器
	bool get_is_trigger() { return is_trigger; };

	//设置是否启用记录上一帧位置
	void set_enable_last_position(bool flag) { enable_last_position = flag; };

	//获取是否启用记录上一帧位置
	bool get_enable_last_position() { return enable_last_position; };
	
	//设置上一帧位置
	void set_last_position(Vector2 position) { last_position = position; };

	//获取上一帧位置
	Vector2 get_last_position() { return last_position; };

	//获取上一帧位置
	Vector2 get_last_position(AnchorMode mode)
	{
		switch (mode)
		{
		case AnchorMode::Centered:
			return last_position;
		case AnchorMode::BottomCrented:
			return { last_position.x,last_position.y + size.y / 2 };
		default:
			return last_position;
		}
	}

private:
	CollisionBox() = default;
	~CollisionBox() = default;


private:
	bool is_trigger = true;
	Vector2 last_position = { 0,0 };

	//是否启用记录上一帧位置
	bool enable_last_position = false;

};


