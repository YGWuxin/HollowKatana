#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <graphics.h>	


using namespace std;

class Controller;
class PlayerController;

class ControllerManager
{
public:
    enum class PlayerType
    {
        None,
        Player_1,
        Player_2
    };

public:
    static ControllerManager& GetInstance()
    {
        static ControllerManager instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }


    //����ָ�����
    void create_player(const PlayerType& type);

    //���ָ�����
    void clear_player(const PlayerType& type)
    {
        if (player_list[type])
            player_list.erase(type);
    };

    // ����ָ���������ӳ��
    void update_player_input_mapping(const PlayerType& type);




    //��ȡ��ҿ�����
    PlayerController* get_player(const PlayerType& type);

    //����AI������
    void create_ai_controller();

    //ɾ��AI������ 
    void remove_ai_controller();

    //����������
    void on_update(float delta);

    //���½�ɫ�������е���������������
    void on_input(const ExMessage& msg);

    // ɾ���������캯���͸�ֵ�����
    ControllerManager(const ControllerManager&) = delete;
    ControllerManager& operator=(const ControllerManager&) = delete;

private:
    unordered_map<PlayerType,Controller*>  player_list;
    vector<Controller*> ai_list;


private:
    ControllerManager() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~ControllerManager() = default;


};

