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
    //获取碰撞箱大小
    Vector2 get_collision_size() {return size;}

    //设置碰撞体大小
    void set_collision_size(Vector2 size);

    Vector2 get_collision_position();

    //设置是否为触发器
    void set_collision_is_trigger(bool is_trigger);

    //设置触发碰撞回调
    void set_hit_actor_callback(function<void(const HitInfo& hit_info)> callback) { hit_actor_callback = callback; }

    //获取当前锚点模式
    AnchorMode get_anchor_mode() { return mode; }

    //设置锚点模式
    void set_anchor_mode(const AnchorMode& mode);

    //设置是否启用模拟物理重力
    void set_enable_gravity(bool val) { enable_gravity = val; }

    //获取是否启用模拟物理重力
    bool get_enable_gravity() { return enable_gravity; }

    //设置是否悬浮在空中
    void set_floating(bool flag) { is_floating = flag; }

    //获取是否悬浮在空中
    bool get_floating() { return is_floating; }

    //设置当前位置
    void set_current_posistion(Vector2 position);

    //获取当前位置
    Vector2 get_current_posistion() { return this->position; }

    //设置当前动画
    void set_current_animation(Animation* animation);

    //设置当前动画
    void set_current_animation_reset(Animation* animation);

    Animation* get_current_animation() { return current_animation; }

    // 设置当前动画帧图片
    void set_current_image(ImageInfo* image_info);

    //设置渲染层级
    void set_render_layer(int l);

    //设置是否朝右
    void set_is_face_rigth(bool is_right) { is_face_rigth = is_right; };

    //获取是否朝右
    bool get_is_face_rigth() { return is_face_rigth; };

    //是否启用碰撞
    void set_enable_collision(bool flag);

    //是否为触发器
    void set_is_collision_trigger(bool flag);

    //设置自己的碰撞层级
    void set_collision_layer_self(CollisionLayer layer);

    //添加可碰撞层级
    void add_collision_layer(CollisionLayer layer);

    //移除可碰撞层级
    void remove_collision_layer(CollisionLayer layer);

    //设置是否可视
    void set_visiable(bool visible);

    //获取是否可视
    bool get_visiable() { return is_visible; }

    //设置重力系数
    void set_gravity(float gravity) { this->gravity = gravity; }

    //获取重力系数
    float get_gravity() { return gravity; }

    //设置空气阻力系数
    bool set_airDrag(float airDrag) { this->airDrag = airDrag; }

    //设置速度
    void set_velocity(float x, float y)
    {
        velocity.x = x;
        velocity.y = y;
    }

    //获取速度
    Vector2 get_velocity() { return velocity; }


    //设置速度X轴
    void set_velocity_x(float x)
    {
        velocity.x = x;
    }

    //设置速度Y轴
    void set_velocity_y(float y)
    {
        velocity.y = y;
    }

    //设置
    void set_render_item_offset(int x, int y)
    {
        item_offset_x = x;
        item_offset_y = y;
    }

    //获取渲染item的偏移
    Vector2 get_render_item_offset()
    {
        return Vector2(item_offset_x, item_offset_y);
    }

    //设置渲染的物体亮度
    void set_render_item_brightness(float brightness);

    //是否开启后处理
    void set_enable_post_process(bool enable);

    //标记为可清除
    void set_is_clear() { is_clear = true; };

    bool get_on_ground() { return on_ground; }

private:
    //处理物理碰撞
    void handle_physics_collision(const HitInfo& hit_info);

protected:
    //item的数据更新
    virtual void on_update(float delta);

    //item的碰撞回调
    virtual void handleCollision(const HitInfo& hit_info) {
        if(hit_actor_callback)
            hit_actor_callback(hit_info);
    };

    //当actor着陆时调用
    virtual void on_land() {};

protected:
    RenderItem* render_item = nullptr;          //用于渲染的item
    AnchorMode mode = AnchorMode::Centered;     //item的位置锚点

    CollisionBox* collision_box = nullptr;      //碰撞箱
    Vector2 size = { 0,0 };                     //碰撞箱大小
    int item_offset_x = 0;                      //item的图片在x轴上的偏移
    int item_offset_y = 0;                      //item的图片在y轴上的偏移

    Vector2 position = { 0,0 };                 //item的位置
    Vector2 velocity = { 0,0 };                 //item的速度
    bool enable_gravity = false;                 //是否启用模拟物理
    float gravity = 1.6e-3f;                    //重力系数
    float airDrag = 0;                          //空气阻力系数


    bool is_face_rigth = true;                  //是否朝右
    bool on_ground = false;                     //是否在地面上

    bool update_animation = true;               //是否更新当前动画

    //外部赋值，不需要销毁
    Animation* current_animation = nullptr;     //itme的当前动画

    bool is_visible = true;                     //当前是否可视

    bool is_clear = false;                      //是否要被销毁

    function<void(const HitInfo& hit_info)> hit_actor_callback;		//触发回调

    //是否悬浮空中
    bool is_floating = false;


    Vector2 last_position = { 0,0 };             //上一次的位置



};

