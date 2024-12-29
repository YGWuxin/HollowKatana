#include "Particle.h"
#include "RenderItem.h"
#include "RenderManager.h"
#include "ImageInfo.h"


Particle::Particle(Vector2 position, int lifespan)
{
	render_item = RenderManager::getInstance().createRenderItem(nullptr, LAYER_ITEM_PARTICLE, false);
	render_item->setAnchorMode(AnchorMode::Centered);
	set_position(position);
	this->lifespan = lifespan;

	animation.pause_animation();
	animation.set_loop(false);
	animation.set_interval(lifespan);
	animation.set_on_finished_callback([&] {
		valid = false;
		});

}


Particle::~Particle()
{
	if (render_item)
	{
		render_item->setCanBeDestroyed(true);
		RenderManager::getInstance().destroyRenderItem(render_item);
		//printf("Particle destroyed");
	}

}


void Particle::set_position(Vector2 position)
{
	this->position = position;
	if (render_item)
	{
		render_item->setPosition(position);
	}
}


void Particle::on_update(float delta)
{
	if (!render_item || type==Type::None)
	{
		valid = false;
		return;
	}
	animation.on_update(delta);
	if (render_item)
	{
		render_item->setImageInfo(animation.get_current_frame_image_info(), animation.get_current_frame_rect_src());
	}
}



void Particle::set_image_info(ImageInfo* image_info)
{
	animation.add_animation(image_info);
	animation.resume_animation();
	type = Type::Image;
}


void Particle::set_atlas(Atlas* atlas)
{
	animation.add_animation(atlas);
	animation.resume_animation();
	type = Type::Atlas;
}