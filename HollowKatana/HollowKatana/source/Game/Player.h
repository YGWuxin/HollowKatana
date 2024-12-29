#pragma once
#include "Charactor.h"
#include "../Utils/Timer.h"
#include "Camera.h"


class ActorManager;
class Controller;
class PlayerController;
class StateMachine;
class Animation;
class WD_Player;

class Player : public Charactor
{
	friend class ActorManager;
	friend class PlayerController;
	friend class Controller;

public:
	void init_input_event() override;

	bool is_rolling_now() const { return is_rolling; };

	bool is_invincible_now() const { return is_invincible; };

	void set_is_invincible_now(bool value) { 
		this->is_invincible = value;
		if (value)
			is_enable_sketch = false;
		else
			is_enable_sketch = true;
	};

	bool get_is_attacking() const { return is_attacking; };

	void set_is_attacking(bool value) { is_attacking = value; };

	void on_hurt(DamageInfo damage_info) override;

	void on_Possess() override;

	void on_UnPossess() override;

	int get_hp() {return player_hp; }

	void set_is_dead(bool value) { is_dead = value; };

	bool get_is_dead() const { return is_dead; };

	Camera* get_camera() { return &player_camera; };

	WD_Player* get_wd_player() { return wd_player; };

protected:
	Player(Vector2 position);

	~Player();

	void on_update(float delta) override;

	void on_land() override;

	

protected:
	void move_right_down();

	void move_right_up();

	void move_left_down();

	void move_left_up();

	void move_on_jump_down();

	void move_on_jump_up();

	void move_on_crouch_down();

	void move_on_crouch_up();


	void move_roll_down();

	void move_roll_up();

	void move_on_attack();

	void move_on_bullet_time_start();

	void move_on_bullet_time_end();

	//��������
	bool reduce_stamina(float value);

private:
	Timer timer_roll;

	bool is_rolling = false;     //�Ƿ񷭹�
	bool is_key_rolling_dowm = false;  //�Ƿ񷭹���

	bool is_attacking = false;   //�Ƿ񹥻�


	float roll_time = 400.0f;  //��������ʱ��
	float roll_speed = 0.9f;   //�����ٶ�

	ActorObject* attack_box = nullptr;  //������

	Animation* attack_effect_right = nullptr;  //������Ч
	Animation* attack_effect_left = nullptr;   //������Ч
	Animation* attack_effect_up = nullptr;     //������Ч
	Animation* attack_effect_down = nullptr;   //������Ч


	float attack_box_pos_x_offset = 0.0f;		 //�����е�x��ƫ����
	float attack_box_pos_y_offset = 0.0f;		 //�����е�y��ƫ����

	bool is_up_key_pressed = false;
	bool is_down_key_pressed = false;


	float current_bullet_time = 1.0f;  //��ǰ���ӵ�ʱ��
	float taget_bullet_time = 1.0f;    //Ŀ����ӵ�ʱ��
	float current_brighness = 1.0f;    //��ǰ������
	float taget_brighness = 1.0f;      //Ŀ�������
	float speed_factor = 5.0f;         //�ٶ�����

	bool is_bullet_time = false;		//�Ƿ�ʼ�ӵ�ʱ��
	bool is_bullet_time_enable = false;  //�Ƿ� enable �ӵ�ʱ��

	//�Ƿ����޵�״̬
	bool is_invincible = false;
	//�޵г���ʱ��
	float invincible_time = 500.0f;

	
	Timer timer_invincible;						//�޵м�ʱ��
	Timer timer_invulnerable_blink;				//�޵�״̬��˸��ʱ��

	IMAGE* sketch_image = nullptr;
	ImageInfo sketch_image_info;
	
	bool is_showing_sketch_frame = false;		//��ǰ֡�Ƿ�Ӧ����ʾ��Ӱ
	bool is_enable_sketch = true;				//�Ƿ�����Ӱ

	WD_Player* wd_player = nullptr;				//��ҵ�UI


	int player_hp = 100;							//��ҵ�Ѫ��

	float player_stamina = 100;								//��ҵ�����
	float player_stamina_start = 100;
	bool is_player_stamina_start = false;					//��������ָ���ʼ��־
	Timer timer_player_stamina_start;						//��ҵ������ָ���ʱ��
	const float PLAYER_ROLL_STAMINA = 23.0f;				//��ҷ������ĵ�����
	const float PLAYER_ATTACK_STAMINA = 7.0f;				//��ҹ������ĵ�����
	const float PLAYER_JUMP_STAMINA = 14.0f;				//��ҹ������ĵ�����

	const float PLAYER_STAMINA_RESTORE_TIME = 1500.0f;		//�ָ���ͣ��ʱ��
	const float PLAYER_STAMINA_RESTORE_SPEED = 40.0f;		//�ָ����ٶ�

	float player_mp = 100;									//��ҵ�ħ��ֵ
	float player_mp_taget = 100;							//��ҵ�ħ��ֵĿ��ֵ
	float player_mp_start = 100;							//��ҵ�ħ��ֵ��ʼֵ
	Timer timer_bullet_time;								//�ӵ�ʱ�俪ʼ��ʱ��
	const float PLAYER_MP_RESTORE_TIME = 2000.0f;			//�ӵ�ʱ���ͣ��ʱ��
	const float PLAYER_MP_RESTORE_SPEED = 35.0f;			//�ָ����ٶ�
	const float PLAYER_MP_REDUCE_SPEED = 30.0f;				//���ٵ��ٶ�
	bool is_player_mp_start = false;						//���ħ���ָ���ʼ��־

	float strenth = 3;				//����ǿ��
	int duration = 200;				//�������
	
	bool is_dead = false;			//�Ƿ�����

	Camera player_camera;								//Ĭ�������
	float camera_pos_x = 10.0f;							//������ƶ��ٶ�
	float last_velocity_x = 0.0f;						//��һ�ε�x���ٶ�
	Vector2 last_position;								//��һ�ε�λ��

};

