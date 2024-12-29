#pragma once

#include "CollisionBox.h"
#include <vector>

using namespace std;

class Camera;

class CollisionManager
{
private:
    vector<CollisionBox*> collision_box_list;

public:
    static CollisionManager& GetInstance()
    {
        static CollisionManager instance; // 静态局部变量，确保唯一性
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    CollisionManager(const CollisionManager&) = delete;
    CollisionManager& operator=(const CollisionManager&) = delete;

    //创建碰撞箱
    CollisionBox* create_collision_box();

    //销毁碰撞箱
    void destroy_collision_box(CollisionBox* box);

    //碰撞执行逻辑
    void process_collide(float delta);

    //记录碰撞箱的上一帧位置
    void record_last_position();

    //碰撞调试函数
    void on_debug_render(const Camera& camera);

    //设置是否开启调试
    void set_enabled_debug(bool flag) { is_enabled_debug = flag; }

    // 当前调试状态
    bool get_enabled_debug() { return is_enabled_debug; }

private:
    bool is_enabled_debug = false;

private:
    CollisionManager() = default;    // 私有构造函数，防止外部创建实例
    ~CollisionManager() = default;


};

