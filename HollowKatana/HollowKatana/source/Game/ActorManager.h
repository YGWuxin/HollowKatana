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
        static ActorManager instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    ActorManager(const ActorManager&) = delete;
    ActorManager& operator=(const ActorManager&) = delete;

    //����ActorObject
    template<typename T, typename... Args>
    T* create_actor(Args&&... args)
    {
        static_assert(std::is_base_of<ActorObject, T>::value, "T must be a subclass of ActorObject");
        T* actor = new T(std::forward<Args>(args)...);  // �����ؼ�ʵ��
        add_actor_to_list(actor);
        return actor;
    }

    //��item��ӵ��б�
    void add_actor_to_list(ActorObject* object);

    //����item
    void destory_actor(ActorObject* object);

    //����item
    void remove_actor(ActorObject* object);

    //����item
    void clear_actors();

    //ִ��update
    void on_update(float delta);



private:
    ActorManager() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~ActorManager() = default;

private:
    vector<ActorObject*> actors_list;
    vector<ActorObject*> actors_list_temp;
    vector<ActorObject*> remove_list;
};

