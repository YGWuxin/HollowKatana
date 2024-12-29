#pragma once
#include "Charactor.h"
#include "../Utils/Timer.h"

class ActorManager;
class StateMachine;
class Animation;
class WD_Hornet;

class Hornet :  public Charactor
{
	friend class ActorManager;
public:
	//�������
	enum class DashType
	{
		NONE,
		GROUND,
		AIR
	};

public:
	void on_hurt(DamageInfo damage_info) override;

	//���ɴ���
	void generate_barbs();

	int get_barbs() {return barb_num;}

	//Ͷ����
	void throw_sword();

	//˿�߹���
	void attack_silk();

	//��̹�����ʼ
	void attack_dash_start(DashType dash_type);

	//��̹�������
	void attack_dash_end(DashType dash_type);

	void set_target(Charactor* target) {
		this->target = nullptr;
		if(target)
			this->target = target;
	}

	Charactor* get_target() {return target;}

	bool get_is_dashing() {return is_dashing;}

	float get_target_distance_x() {return target_distance_x;}

	//��ȡ����ֵ
	int get_hp() {return hp;}

	bool is_invincible_now() const { return is_invincible; };

	void set_is_last_face_right(bool is_right) { is_last_face_right = is_right; }

	bool get_is_last_face_right() const { return is_last_face_right; }

protected:
	Hornet(Vector2 position);

	~Hornet();

	void on_update(float delta) override;

	void on_land() override;

	void handleCollision(const HitInfo& hit_info) override;


private:
	ActorObject* attack_silk_box = nullptr;		//˿�߹�����
	ActorObject* attack_dash_box = nullptr;		//��̹�����

	Animation* attack_effect_right = nullptr;  //������Ч
	Animation* attack_effect_left = nullptr;   //������Ч

	float attack_silk_pos_x_offset = 0.0f;		 //�����е�x��ƫ����
	float attack_silk_pos_y_offset = -75.0f;		 //�����е�y��ƫ����

	float attack_dash_pos_x_offset = 0.0f;		 //�����е�x��ƫ����
	float attack_dash_pos_y_offset = -75.0f;		 //�����е�y��ƫ����


	int barb_num = 0;								//��������
	const int MAX_BARB_NUM = 6;						//����������

	Charactor* target = nullptr;					//Ŀ��
	Vector2 target_pos = Vector2(0,0);							//Ŀ��λ��


	//�������ٶ�
	const float DASH_SPEED_GROUND = 1.5f;
	//���г���ٶ�
	const float DASH_SPEED_AIR = 2.5f;

	DashType dash_type = DashType::NONE;			//�������

	bool is_dashing = false;						//�Ƿ����ڳ��

	int hp = 100;									//����ֵ

	float target_distance_x = 0.0f;					//Ŀ�����


	//�Ƿ����޵�״̬
	bool is_invincible = false;
	//�޵г���ʱ��
	float invincible_time = 500.0f;


	Timer timer_invincible;						//�޵м�ʱ��
	Timer timer_invulnerable_blink;				//�޵�״̬��˸��ʱ��

	IMAGE* sketch_image = nullptr;
	ImageInfo sketch_image_info;

	bool is_showing_sketch_frame = false;		//��ǰ֡�Ƿ�Ӧ����ʾ��Ӱ
	bool is_enable_sketch = false;				//�Ƿ�����Ӱ


	WD_Hornet* wd_hornet = nullptr;

	bool is_last_face_right = true;				//��һ֡�Ƿ����泯��
};

