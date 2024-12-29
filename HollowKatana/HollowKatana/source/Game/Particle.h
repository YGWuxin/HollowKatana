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
	int timer = 0;							//���Ӷ������ŵĶ�ʱ��
	int lifespan = 0;						//��֡���Ӷ�������ʱ��
	int  idx_frame = 0;						//��ǰ���ڲ��ŵĶ���֡
	Vector2 position = { 0,0 };				//���ӵ���������λ��
	bool valid = true;						//�����Ƿ���Ч
	RenderItem* render_item = nullptr;		//����Ⱦ��ʵ�壬��Ҫ�ֶ�ɾ��
	Atlas* atlas = nullptr;					//���Ӷ���ʹ�õ�ͼ��
	ImageInfo* image_info = nullptr;		//���Ӷ���ʹ�õ�ͼƬ��Ϣ
	Type type = Type::None;					//��������


	Animation animation;					//���Ӷ���

};
