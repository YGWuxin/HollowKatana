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
        static CollisionManager instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    CollisionManager(const CollisionManager&) = delete;
    CollisionManager& operator=(const CollisionManager&) = delete;

    //������ײ��
    CollisionBox* create_collision_box();

    //������ײ��
    void destroy_collision_box(CollisionBox* box);

    //��ײִ���߼�
    void process_collide(float delta);

    //��¼��ײ�����һ֡λ��
    void record_last_position();

    //��ײ���Ժ���
    void on_debug_render(const Camera& camera);

    //�����Ƿ�������
    void set_enabled_debug(bool flag) { is_enabled_debug = flag; }

    // ��ǰ����״̬
    bool get_enabled_debug() { return is_enabled_debug; }

private:
    bool is_enabled_debug = false;

private:
    CollisionManager() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~CollisionManager() = default;


};

