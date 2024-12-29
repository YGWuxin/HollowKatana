#pragma once

#include <vector>
#include "Vector2.h"

using namespace std;

class ActorObject;

class ActorManager
{
public:
    static ActorManager& GetInstance()
    {
        static ActorManager instance; // 静态局部变量，确保唯一性
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    ActorManager(const ActorManager&) = delete;
    ActorManager& operator=(const ActorManager&) = delete;

    //创建ActorObject
    template<typename T, typename... Args>
    T* create_actor(Args&&... args)
    {
        static_assert(std::is_base_of<ActorObject, T>::value, "T must be a subclass of ActorObject");
        T* actor = new T(std::forward<Args>(args)...);  // 创建控件实例
        add_actor_to_list(actor);
        return actor;
    }

    //将item添加到列表
    void add_actor_to_list(ActorObject* object);

    //销毁item
    void destory_actor(ActorObject* object);

    //销毁item
    void remove_actor(ActorObject* object);

    //销毁item
    void clear_actors();

    //执行update
    void on_update(float delta);



private:
    ActorManager() = default;    // 私有构造函数，防止外部创建实例
    ~ActorManager() = default;

private:
    vector<ActorObject*> actors_list;
    vector<ActorObject*> actors_list_temp;
    vector<ActorObject*> remove_list;
};

