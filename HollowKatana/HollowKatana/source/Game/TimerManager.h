#pragma once


class TimerManager
{
public:
    enum class TimerType
    {
        GameTime,
        RealTime,
    };

public:
    static TimerManager& GetInstance()
    {
        static TimerManager instance; // 静态局部变量，确保唯一性
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    TimerManager(const TimerManager&) = delete;
    TimerManager& operator=(const TimerManager&) = delete;


private:
    TimerManager() = default;    // 私有构造函数，防止外部创建实例
    ~TimerManager() = default;   // 私有析构函数，防止外部销毁实例


public:
    void on_update(float delta);

    //获取游戏时间
    float get_game_time() const { return game_time; }

    //获取现实时间
    float get_real_time() const { return real_time; }

    //设置全局时间膨胀系数
    void set_time_dilation(float dilation) { time_dilation = dilation; }

    void lerp_float(float& current_value, float target_value, float speed, TimerType timer_type);

    void lerp_float(float& current_value, float target_value, float speed, float delta);

    void lerp_float(float& current_value, float start_value, float end_value, float speed, float delta);

    void lerp_float(float& current_value, float start_value, float end_value, float speed, TimerType timer_type);

    bool is_valid_frame() const { return is_vaild_frame; }


private:
    //全局时间膨胀系数
    float time_dilation = 1.0f;
    //现实时间
    float real_time = 0.0f;
    //游戏时间
    float game_time = 0.0f;

    float delta_time = 0.0f;
    float last_frame_time = 0.0f;


    // 物理模拟的相关变量
    float accumulator = 0.0f;
    const float fixedTimestep = 12.0f;      // 固定时间步长, 5ms

    bool is_vaild_frame = true;            // 是否是有效帧



};

