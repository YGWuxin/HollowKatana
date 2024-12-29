#include "CollisionManager.h"
#include "Camera.h"
#include "../Utils/helper.h"
#include <math.h>
#include <graphics.h>	
#include "ActorObject.h"

using namespace std;

CollisionBox* CollisionManager::create_collision_box()
{
	CollisionBox* box = new CollisionBox();
	collision_box_list.push_back(box);
	return box;
}


void CollisionManager::destroy_collision_box(CollisionBox* box)
{
	collision_box_list.erase(std::remove(collision_box_list.begin(), collision_box_list.end(), box), collision_box_list.end());
	delete box;
}



void CollisionManager::process_collide(float delta)
{
	for (CollisionBox* collision_box_src : collision_box_list)
	{
		if (!collision_box_src->get_enabled() || collision_box_src->layer_dst == (int)CollisionLayer::None)
			continue;

		for (CollisionBox* collision_box_dst : collision_box_list)
		{
			if (!collision_box_src->get_enabled())
				break;

			int res = (int)(collision_box_dst->get_layer_self()) & collision_box_src->get_layer_dst();
			if (res == 0 || !collision_box_dst->get_enabled() || collision_box_src == collision_box_dst)
				continue;
	

			float abs_x = abs(collision_box_src->get_position().x - collision_box_dst->get_position().x);
			float abs_y = abs(collision_box_src->get_position().y - collision_box_dst->get_position().y);
			float collisin_size_x = collision_box_src->get_size().x / 2 + collision_box_dst->get_size().x / 2;
			float collisin_size_y = collision_box_src->get_size().y / 2 + collision_box_dst->get_size().y / 2;

			float distancex = abs_x - collisin_size_x;
			float distancey = abs_y - collisin_size_y;

			bool is_collide_x = abs_x <= collisin_size_x;
			bool is_collide_y = abs_y <= collisin_size_y;


			if (is_collide_x && is_collide_y && collision_box_src->on_collide)
			{
				HitInfo info;
				info.actor = collision_box_dst->actor_object;
				info.box = collision_box_dst;
				info.delta = delta;
				info.size = collision_box_dst->get_size();
				info.position = collision_box_dst->position;
				info.distance = { distancex, distancey };
				info.normal = { collisin_size_x, collisin_size_y };
				info.layer = collision_box_dst->layer_self;
				collision_box_src->on_collide(info);
			}

		}
	}
}


void CollisionManager::record_last_position()
{
	for (CollisionBox* collision_box_src : collision_box_list)
	{
		if (!collision_box_src->get_enabled() || collision_box_src->layer_dst == (int)CollisionLayer::None)
			continue;
		ActorObject* actor_object = collision_box_src->actor_object;
		if(!actor_object)
			continue;
		if (actor_object->get_enable_gravity())
		{
			//printf("record_last_position\r\n");
			//printf("collision_box_src: %s\n", typeid(*actor_object).name());
			collision_box_src->set_last_position(collision_box_src->get_position());
			//printf("record_last_position x:%f, y:%f\r\n", collision_box_src->get_last_position().x, collision_box_src->get_last_position().y);
		}
	}
}


void CollisionManager::on_debug_render(const Camera& camera)
{
	if (!is_enabled_debug)
		return;
	settextcolor(RGB(255, 0, 0));
	setfont(24, 0, _T("仿宋_GB2312"));
	outtextxy(15,15,_T("调试模式已开启，按'Q'键关闭"));
	for (CollisionBox* box : collision_box_list) {
		if (box)
		{
			//helper::putimage_ex(camera, item->image, &item->rect_dst, &item->rect_src);
			setlinecolor(box->get_enabled() ? RGB(255,195,195) : RGB(115,115,175));
			rectangle((int)(box->get_position().x - box->get_size().x / 2 + camera.get_position().x),
					  (int)(box->get_position().y - box->get_size().y / 2 + camera.get_position().y),
					  (int)(box->get_position().x + box->get_size().x / 2 + camera.get_position().x),
					  (int)(box->get_position().y + box->get_size().y / 2 + camera.get_position().y));
		}
	}
}

