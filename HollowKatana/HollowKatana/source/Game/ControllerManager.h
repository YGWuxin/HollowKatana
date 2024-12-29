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
        static ControllerManager instance; // 静态局部变量，确保唯一性
        return instance;
    }


    //创建指定玩家
    void create_player(const PlayerType& type);

    //清除指定玩家
    void clear_player(const PlayerType& type)
    {
        if (player_list[type])
            player_list.erase(type);
    };

    // 更新指定玩家输入映射
    void update_player_input_mapping(const PlayerType& type);




    //获取玩家控制器
    PlayerController* get_player(const PlayerType& type);

    //创建AI控制器
    void create_ai_controller();

    //删除AI控制器 
    void remove_ai_controller();

    //控制器更新
    void on_update(float delta);

    //更新角色管理器中的所有玩家输入更新
    void on_input(const ExMessage& msg);

    // 删除拷贝构造函数和赋值运算符
    ControllerManager(const ControllerManager&) = delete;
    ControllerManager& operator=(const ControllerManager&) = delete;

private:
    unordered_map<PlayerType,Controller*>  player_list;
    vector<Controller*> ai_list;


private:
    ControllerManager() = default;    // 私有构造函数，防止外部创建实例
    ~ControllerManager() = default;


};

