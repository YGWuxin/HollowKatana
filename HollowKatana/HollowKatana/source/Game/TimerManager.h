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
        static TimerManager instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    TimerManager(const TimerManager&) = delete;
    TimerManager& operator=(const TimerManager&) = delete;


private:
    TimerManager() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~TimerManager() = default;   // ˽��������������ֹ�ⲿ����ʵ��


public:
    void on_update(float delta);

    //��ȡ��Ϸʱ��
    float get_game_time() const { return game_time; }

    //��ȡ��ʵʱ��
    float get_real_time() const { return real_time; }

    //����ȫ��ʱ������ϵ��
    void set_time_dilation(float dilation) { time_dilation = dilation; }

    void lerp_float(float& current_value, float target_value, float speed, TimerType timer_type);

    void lerp_float(float& current_value, float target_value, float speed, float delta);

    void lerp_float(float& current_value, float start_value, float end_value, float speed, float delta);

    void lerp_float(float& current_value, float start_value, float end_value, float speed, TimerType timer_type);

    bool is_valid_frame() const { return is_vaild_frame; }


private:
    //ȫ��ʱ������ϵ��
    float time_dilation = 1.0f;
    //��ʵʱ��
    float real_time = 0.0f;
    //��Ϸʱ��
    float game_time = 0.0f;

    float delta_time = 0.0f;
    float last_frame_time = 0.0f;


    // ����ģ�����ر���
    float accumulator = 0.0f;
    const float fixedTimestep = 12.0f;      // �̶�ʱ�䲽��, 5ms

    bool is_vaild_frame = true;            // �Ƿ�����Ч֡



};

