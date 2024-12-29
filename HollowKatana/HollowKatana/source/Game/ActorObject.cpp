#include "ActorObject.h"
#include <cstdio>
//#include "Controller.h"
#include "RenderItem.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "ImageInfo.h"

ActorObject::ActorObject(Vector2 position)
{
	this->position = position;
	mode = AnchorMode::Centered;
	render_item = RenderManager::getInstance().createRenderItem(nullptr, 0, false);
	render_item->setAnchorMode(mode);														//设置锚点模式
	render_item->setPosition(position, item_offset_x, item_offset_y);						//设置初始位置

	collision_box = CollisionManager::GetInstance().create_collision_box();					//创建碰撞体
	collision_box->set_item_object(this);													//设置碰撞体所属物体
	collision_box->set_layer_self(CollisionLayer::None);									//设置碰撞体所属层
	collision_box->set_enabled(true);														//设置碰撞体是否可用
	collision_box->set_is_trigger(false);													//设置碰撞体不为触发器
	collision_box->set_size(size);															//设置碰撞体大小
	collision_box->set_position(position, mode);											//设置碰撞体初始位置和锚点模式
	collision_box->set_on_collide([&](HitInfo hit_info) {
		this->handle_physics_collision(hit_info);
		this->handleCollision(hit_info);
		});
}


ActorObject::~ActorObject()
{
	if (render_item)
	{
		render_item->setCanBeDestroyed(true);
		RenderManager::getInstance().destroyRenderItem(render_item);
	}
	if (collision_box)
	{
		CollisionManager::GetInstance().destroy_collision_box(collision_box);
	}
	//printf("ActorObject Destructor\n");
}

void ActorObject::on_update(float delta)
{

	if(!is_visible)
		return;

	//printf("Velocity_x: %0.1f\n", velocity.x);


	//简单物理模拟部分
	if (enable_gravity && collision_box && !collision_box->get_is_trigger())
	{
		if (!is_floating)
		{
			if (velocity.y == 0)
				on_ground = true;
			else
				on_ground = false;

			velocity.y += gravity * delta;
		}
		else
		{
			on_ground = false;
		}
	
		if (airDrag != 0 && velocity.x != 0)
		{
			if (velocity.x > 0)
			{
				velocity.x -= airDrag * delta;
				if (velocity.x <= 0)
					velocity.x = 0;
			}
			else if (velocity.x < 0)
			{
				velocity.x += airDrag * delta;
				if (velocity.x >= 0)
					velocity.x = 0;
			}
		}
	}
	last_position = position;
	position += velocity * delta;
	//printf("last_position: %0.1f, %0.1f\n", last_position.x, last_position.y);
	//printf("position: %0.1f, %0.1f\n", position.x, position.y);
	//printf("position_x_delta: %0.1f\n", (position.x - last_position.x));
	



	if (current_animation && update_animation)
	{
		current_animation->on_update(delta);		//更新动画
	}


	if (render_item )
	{
		render_item->setPosition(position,item_offset_x, item_offset_y);
		if(current_animation && update_animation)
			render_item->setImageInfo(current_animation->get_current_frame_image_info(), current_animation->get_current_frame_rect_src());
	}

	//碰撞体
	if (collision_box)
		collision_box->set_position(position, mode);
}

void ActorObject::set_enable_collision(bool flag)
{
	if (collision_box)
		collision_box->set_enabled(flag);
}

//设置当前位置
void ActorObject::set_current_posistion(Vector2 position)
{
	this->position = position;
	if(collision_box)
		collision_box->set_position(position, mode);
	if (render_item)
		render_item->setPosition(position, item_offset_x, item_offset_y);
}

void ActorObject::set_anchor_mode(const AnchorMode& mode)
{
	this->mode = mode;
	if (render_item)
		render_item->setAnchorMode(mode);
	if (collision_box)
		collision_box->set_position(position, mode);
}


void ActorObject::set_render_layer(int l)
{
	if (render_item)
		render_item->setLayer(l);
}

void ActorObject::set_current_animation(Animation* animation)
{
	current_animation = animation;
	if (!current_animation)
		return;
	if (render_item)
	{
		render_item->setImageInfo(current_animation->get_current_frame_image_info(), current_animation->get_current_frame_rect_src());
	}
}


void ActorObject::set_current_animation_reset(Animation* animation)
{
	current_animation = animation;
	if (!current_animation)
		return;
	current_animation->reset();
	if (render_item)
	{
		render_item->setImageInfo(current_animation->get_current_frame_image_info(), current_animation->get_current_frame_rect_src());
	}
}

void ActorObject::set_current_image(ImageInfo* image_info)
{
	if (render_item)
	{
		render_item->setImageInfo(image_info);
	}
}

void ActorObject::set_collision_layer_self(CollisionLayer layer)
{
	if (!collision_box)
		return;
	collision_box->set_layer_self(layer);									//设置碰撞体所属层
}


//设置碰撞体大小
void ActorObject::set_collision_size(Vector2 size)
{
	this->size = size;
	if (collision_box)
		collision_box->set_size(size);
}

//获取碰撞体的位置
Vector2 ActorObject::get_collision_position()
{
	if (collision_box)
		return collision_box->get_position(mode);
	return { 0,0 };
}

//添加可碰撞层级
void ActorObject::add_collision_layer(CollisionLayer layer)
{
	if (collision_box)
		collision_box->add_layer_dst(layer);
}

//移除可碰撞层级
void ActorObject::remove_collision_layer(CollisionLayer layer)
{
	if (collision_box)
		collision_box->remove_layer_dst(layer);
}


void ActorObject::set_is_collision_trigger(bool flag)
{
	if (collision_box)
		collision_box->set_is_trigger(flag);
}


//设置Item是否可视
void ActorObject::set_visiable(bool visible)
{
	is_visible = visible;
	if (render_item)
	{
		render_item->setCanRender(is_visible);
	}
	if (collision_box)
		collision_box->set_enabled(is_visible);
}

void ActorObject::set_collision_is_trigger(bool is_trigger)
{
	if (!collision_box)
		return;
	collision_box->set_is_trigger(is_trigger);
}


void ActorObject::handle_physics_collision(const HitInfo& hit_info)
{
	if (!collision_box)
		return;
	if(collision_box->get_is_trigger() || hit_info.box->get_is_trigger() || !enable_gravity)
		return;

	float last_tick_pos_x = collision_box->get_last_position(mode).x;
	float last_tick_pos_y = collision_box->get_last_position(mode).y;

	float distance_x = collision_box->get_last_position().x - hit_info.position.x;
	float distance_y = collision_box->get_last_position().y - hit_info.position.y;

	float distance_delta_x = abs(distance_x) - hit_info.normal.x;
	float distance_delta_y = abs(distance_y) - hit_info.normal.y;

	//
	//system("cls");

	if (distance_delta_y > distance_delta_x)
	{
		bool is_up = get_collision_position().y - hit_info.position.y < 0;
		if (velocity.y > 0 && is_up)
		{
			if (last_tick_pos_y <= (hit_info.position.y - hit_info.size.y / 2))
			{
				switch (mode)
				{
				case AnchorMode::Centered:
					set_current_posistion({ position.x, (hit_info.position.y - hit_info.size.y / 2 - size.y / 2) });
					break;
				case AnchorMode::BottomCrented:
					set_current_posistion({ position.x, (hit_info.position.y - hit_info.size.y / 2) });
					break;
				default:
					break;
				}
				
				velocity.y = 0;
				if (!on_ground && !is_floating)
				{
					on_land();
					//printf("Velocity.x:%f,Velocity.y:%f\r\n", velocity.x, velocity.y);
					
				}
				on_ground = true;
				return;
			}
		}

		if (velocity.y < 0 && !is_up)
		{
			if (last_tick_pos_y >= (hit_info.position.y + hit_info.size.y / 2))
			{
				switch (mode)
				{
				case AnchorMode::Centered:
					set_current_posistion({ position.x, (hit_info.position.y + hit_info.size.y / 2 + size.y / 2) });
					break;
				case AnchorMode::BottomCrented:
					set_current_posistion({ position.x, (hit_info.position.y + hit_info.size.y / 2 + size.y) });
					break;
				default:
					break;
				}
				velocity.y = 0;
				return;
			}
		}
	}

	else if (distance_delta_x > distance_delta_y)
	{
		bool is_right = get_collision_position().x - hit_info.position.x > 0;
		if (velocity.x > 0 && !is_right)
		{
			float last_tick_pos_x = collision_box->get_last_position(mode).x + size.x / 2;
			if (last_tick_pos_x >= (hit_info.position.x - hit_info.size.x / 2))
			{
				set_current_posistion({ (hit_info.position.x - hit_info.size.x / 2 - size.x / 2), position.y });
				velocity.x = 0;
				//printf("hit_info.position.x:%f,hit_info.position.y:%f,hit_info.size.x:%f,hit_info.size.y:%f\r\n", hit_info.position.x, hit_info.position.y, hit_info.size.x, hit_info.size.y);
				//printf("Position.x:%f,Position.y:%f\r\n", position.x, position.y);
				return;
			}
		}

		if (velocity.x < 0 && is_right)
		{
			float last_tick_pos_x = collision_box->get_last_position(mode).x - size.x / 2;
			if (last_tick_pos_x <= (hit_info.position.x + hit_info.size.x / 2))
			{
				set_current_posistion({ (hit_info.position.x + hit_info.size.x / 2 + size.x / 2), position.y });
				velocity.x = 0;
				return;
			}
		}
	}

	//printf("distance_x:%f,distance_y:%f\r\n", distance_x, distance_y);
	//printf("distance_delta_x:%f,distance_delta_y:%f\r\n", distance_delta_x, distance_delta_y);


}


//设置渲染的物体亮度
void ActorObject::set_render_item_brightness(float brightness)
{
	if (render_item)
	{
		render_item->setBrightness(brightness);
		
	}
}

//是否开启后处理
void ActorObject::set_enable_post_process(bool enable)
{
	if (render_item)
		render_item->setPostProcessed(enable);
}


