#pragma once

#include "Vector2.h"
#include "CollisionBox.h"
#include "Animation.h"
#include <functional>
#include <unordered_map>
#include <string>
#include "../Parameter/GlobeGameParameters.h"


using namespace std;

class RenderItem;
class ActorManager;


class ActorObject {
    friend class ActorManager;


protected:
    ActorObject(Vector2 position);

   virtual ~ActorObject();

public:
    //��ȡ��ײ���С
    Vector2 get_collision_size() {return size;}

    //������ײ���С
    void set_collision_size(Vector2 size);

    Vector2 get_collision_position();

    //�����Ƿ�Ϊ������
    void set_collision_is_trigger(bool is_trigger);

    //���ô�����ײ�ص�
    void set_hit_actor_callback(function<void(const HitInfo& hit_info)> callback) { hit_actor_callback = callback; }

    //��ȡ��ǰê��ģʽ
    AnchorMode get_anchor_mode() { return mode; }

    //����ê��ģʽ
    void set_anchor_mode(const AnchorMode& mode);

    //�����Ƿ�����ģ����������
    void set_enable_gravity(bool val) { enable_gravity = val; }

    //��ȡ�Ƿ�����ģ����������
    bool get_enable_gravity() { return enable_gravity; }

    //�����Ƿ������ڿ���
    void set_floating(bool flag) { is_floating = flag; }

    //��ȡ�Ƿ������ڿ���
    bool get_floating() { return is_floating; }

    //���õ�ǰλ��
    void set_current_posistion(Vector2 position);

    //��ȡ��ǰλ��
    Vector2 get_current_posistion() { return this->position; }

    //���õ�ǰ����
    void set_current_animation(Animation* animation);

    //���õ�ǰ����
    void set_current_animation_reset(Animation* animation);

    Animation* get_current_animation() { return current_animation; }

    // ���õ�ǰ����֡ͼƬ
    void set_current_image(ImageInfo* image_info);

    //������Ⱦ�㼶
    void set_render_layer(int l);

    //�����Ƿ���
    void set_is_face_rigth(bool is_right) { is_face_rigth = is_right; };

    //��ȡ�Ƿ���
    bool get_is_face_rigth() { return is_face_rigth; };

    //�Ƿ�������ײ
    void set_enable_collision(bool flag);

    //�Ƿ�Ϊ������
    void set_is_collision_trigger(bool flag);

    //�����Լ�����ײ�㼶
    void set_collision_layer_self(CollisionLayer layer);

    //��ӿ���ײ�㼶
    void add_collision_layer(CollisionLayer layer);

    //�Ƴ�����ײ�㼶
    void remove_collision_layer(CollisionLayer layer);

    //�����Ƿ����
    void set_visiable(bool visible);

    //��ȡ�Ƿ����
    bool get_visiable() { return is_visible; }

    //��������ϵ��
    void set_gravity(float gravity) { this->gravity = gravity; }

    //��ȡ����ϵ��
    float get_gravity() { return gravity; }

    //���ÿ�������ϵ��
    bool set_airDrag(float airDrag) { this->airDrag = airDrag; }

    //�����ٶ�
    void set_velocity(float x, float y)
    {
        velocity.x = x;
        velocity.y = y;
    }

    //��ȡ�ٶ�
    Vector2 get_velocity() { return velocity; }


    //�����ٶ�X��
    void set_velocity_x(float x)
    {
        velocity.x = x;
    }

    //�����ٶ�Y��
    void set_velocity_y(float y)
    {
        velocity.y = y;
    }

    //����
    void set_render_item_offset(int x, int y)
    {
        item_offset_x = x;
        item_offset_y = y;
    }

    //��ȡ��Ⱦitem��ƫ��
    Vector2 get_render_item_offset()
    {
        return Vector2(item_offset_x, item_offset_y);
    }

    //������Ⱦ����������
    void set_render_item_brightness(float brightness);

    //�Ƿ�������
    void set_enable_post_process(bool enable);

    //���Ϊ�����
    void set_is_clear() { is_clear = true; };

    bool get_on_ground() { return on_ground; }

private:
    //����������ײ
    void handle_physics_collision(const HitInfo& hit_info);

protected:
    //item�����ݸ���
    virtual void on_update(float delta);

    //item����ײ�ص�
    virtual void handleCollision(const HitInfo& hit_info) {
        if(hit_actor_callback)
            hit_actor_callback(hit_info);
    };

    //��actor��½ʱ����
    virtual void on_land() {};

protected:
    RenderItem* render_item = nullptr;          //������Ⱦ��item
    AnchorMode mode = AnchorMode::Centered;     //item��λ��ê��

    CollisionBox* collision_box = nullptr;      //��ײ��
    Vector2 size = { 0,0 };                     //��ײ���С
    int item_offset_x = 0;                      //item��ͼƬ��x���ϵ�ƫ��
    int item_offset_y = 0;                      //item��ͼƬ��y���ϵ�ƫ��

    Vector2 position = { 0,0 };                 //item��λ��
    Vector2 velocity = { 0,0 };                 //item���ٶ�
    bool enable_gravity = false;                 //�Ƿ�����ģ������
    float gravity = 1.6e-3f;                    //����ϵ��
    float airDrag = 0;                          //��������ϵ��


    bool is_face_rigth = true;                  //�Ƿ���
    bool on_ground = false;                     //�Ƿ��ڵ�����

    bool update_animation = true;               //�Ƿ���µ�ǰ����

    //�ⲿ��ֵ������Ҫ����
    Animation* current_animation = nullptr;     //itme�ĵ�ǰ����

    bool is_visible = true;                     //��ǰ�Ƿ����

    bool is_clear = false;                      //�Ƿ�Ҫ������

    function<void(const HitInfo& hit_info)> hit_actor_callback;		//�����ص�

    //�Ƿ���������
    bool is_floating = false;


    Vector2 last_position = { 0,0 };             //��һ�ε�λ��



};

