#pragma once


#define MAX_ALIAS_LENGTH            34                  //标识符长度
#define MAX_SOUNDS                  64                  //同时所能播放的音效，可以理解为播放通道

#define AUDIO_VOLUM                 200                 //音效音量大小


class AudioManager
{
public:
    //音效类型
    enum class AudioType
    {
        None,
        Music,
        Effect
    };

    // 音效结构体
    struct SoundInfo {
        char alias[32] = { 0 };
        //初始音量
        float volume = 1.0f;
        AudioType type = AudioType::None;
        bool isLoop = false;
    };

public:
    static AudioManager& GetInstance()
    {
        static AudioManager instance; // 静态局部变量，确保唯一性
        return instance;
    }


    // 删除拷贝构造函数和赋值运算符
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
    AudioManager() = default;    // 私有构造函数，防止外部创建实例
    ~AudioManager() = default;

    void LoadSoundByAlias(const char* filename, const char* alias);

private:
    SoundInfo SoundInfos[MAX_SOUNDS];
    int pCurrent = 0;                                       //音效索引

    int MusicVolume = 100;                                  //音乐音量
    int EffectVolume = 100;                                 //音效音量
};

