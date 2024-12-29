#pragma once

#include "Vector2.h"
#include "atlas.h"
#include "Animation.h"

class RenderItem;
class ImageInfo;

class Particle
{
public:
	enum class Type
	{
		None,
		Atlas,
		Image
	};

public:
	Particle(Vector2 position, int lifespan);
	~Particle();

	void on_update(float delta);

	void set_position(Vector2 position);

	Vector2 get_position() { return position; }

	bool check_valid() { return valid; }

	void set_atlas(Atlas* atlas);

	void set_image_info(ImageInfo* image_info);

	//void set_lifespan(int lifespan) { this->lifespan = lifespan; }

private:
	int timer = 0;							//粒子动画播放的定时器
	int lifespan = 0;						//单帧粒子动画持续时长
	int  idx_frame = 0;						//当前正在播放的动画帧
	Vector2 position = { 0,0 };				//粒子的世界坐标位置
	bool valid = true;						//粒子是否有效
	RenderItem* render_item = nullptr;		//被渲染的实体，需要手动删除
	Atlas* atlas = nullptr;					//粒子动画使用的图集
	ImageInfo* image_info = nullptr;		//粒子动画使用的图片信息
	Type type = Type::None;					//粒子类型


	Animation animation;					//粒子动画

};

