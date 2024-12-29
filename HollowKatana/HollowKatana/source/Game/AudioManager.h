#pragma once


#define MAX_ALIAS_LENGTH            34                  //��ʶ������
#define MAX_SOUNDS                  64                  //ͬʱ���ܲ��ŵ���Ч���������Ϊ����ͨ��

#define AUDIO_VOLUM                 200                 //��Ч������С


class AudioManager
{
public:
    //��Ч����
    enum class AudioType
    {
        None,
        Music,
        Effect
    };

    // ��Ч�ṹ��
    struct SoundInfo {
        char alias[32] = { 0 };
        //��ʼ����
        float volume = 1.0f;
        AudioType type = AudioType::None;
        bool isLoop = false;
    };

public:
    static AudioManager& GetInstance()
    {
        static AudioManager instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }


    // ɾ���������캯���͸�ֵ�����
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;


    const char* PlaySoundAudio(const char* filename, int volume = AUDIO_VOLUM, bool repeat = false);

    const char* PlaySoundAudio(const char* filename, bool repeat = false);

    const char* PlaySoundAudio(const char* filename, AudioType type, bool repeat = false);

    const char* PlaySoundAudio(const char* filename, AudioType type,int volume, bool repeat = false);

    void StopSound(const char* alias, bool isClear = true);

    void SetVolume(const char* alias, int volume);
   
    void SetMusicVolume(int volume);

    void SetEffectVolume(int volume);

    int GetMusicVolume() { return MusicVolume; }

    int GetSoundVolume() { return EffectVolume; }

private:
    AudioManager() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~AudioManager() = default;

    void LoadSoundByAlias(const char* filename, const char* alias);

private:
    SoundInfo SoundInfos[MAX_SOUNDS];
    int pCurrent = 0;                                       //��Ч����

    int MusicVolume = 100;                                  //��������
    int EffectVolume = 100;                                 //��Ч����
};

