#include "AudioManager.h"
#include <cstdio>
#include <windows.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib") 


const char* AudioManager::PlaySoundAudio(const char* filename,int volume, bool repeat)
{
    static bool initialized = FALSE;

    if (!initialized) {
        for (int i = 0; i < MAX_SOUNDS; i++)
        {
            snprintf(SoundInfos[i].alias, sizeof(SoundInfos[i].alias), "audio%d", i);
        }
        initialized = TRUE;
    }

    //判断当前的音效是否在循环播放
    int i;
    for (i = 0; i < MAX_SOUNDS; i++)
    {
        if (!SoundInfos[pCurrent].isLoop) {
            break;
        }
        pCurrent++;
        if (pCurrent >= MAX_SOUNDS) {
            pCurrent = 0;
        }
    }
    //如果所有音效均在循环播放中，则不进行音效生成
    if (i >= MAX_SOUNDS)    return NULL;


    // 打开并播放音效，使用定义好的别名
    char command[256];

    LoadSoundByAlias(filename, SoundInfos[pCurrent].alias);

    SetVolume(SoundInfos[pCurrent].alias, volume);      //对wav不生效

    // 播放音效
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", SoundInfos[pCurrent].alias);     //对wav不生效
    }
    else {
        snprintf(command, sizeof(command), "play %s", SoundInfos[pCurrent].alias);
    }
    mciSendStringA(command, NULL, 0, NULL);

    SoundInfos[pCurrent].isLoop = repeat;
    int index = pCurrent;
    pCurrent = (pCurrent + 1) % MAX_SOUNDS;

    return SoundInfos[index].alias;

}


const char* AudioManager::PlaySoundAudio(const char* filename, bool repeat)
{
    static bool initialized = FALSE;

    if (!initialized) {
        for (int i = 0; i < MAX_SOUNDS; i++)
        {
            snprintf(SoundInfos[i].alias, sizeof(SoundInfos[i].alias), "audio%d", i);
        }
        initialized = TRUE;
    }

    //判断当前的音效是否在循环播放
    int i;
    for (i = 0; i < MAX_SOUNDS; i++)
    {
        if (!SoundInfos[pCurrent].isLoop) {
            break;
        }
        pCurrent++;
        if (pCurrent >= MAX_SOUNDS) {
            pCurrent = 0;
        }
    }
    //如果所有音效均在循环播放中，则不进行音效生成
    if (i >= MAX_SOUNDS)    return NULL;

    SoundInfos[pCurrent].volume = 1.0f;

    // 打开并播放音效，使用定义好的别名
    char command[256];

    LoadSoundByAlias(filename, SoundInfos[pCurrent].alias);

  //  SetVolume(soundEffects[pCurrent].alias, AUDIO_VOLUM);      //对wav不生效

    // 播放音效
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", SoundInfos[pCurrent].alias);     //对wav不生效
    }
    else {
        snprintf(command, sizeof(command), "play %s", SoundInfos[pCurrent].alias);
    }
    mciSendStringA(command, NULL, 0, NULL);

    SoundInfos[pCurrent].isLoop = repeat;
    int index = pCurrent;
    pCurrent = (pCurrent + 1) % MAX_SOUNDS;

    return SoundInfos[index].alias;

}

const char* AudioManager::PlaySoundAudio(const char* filename, AudioType type, bool repeat)
{
    static bool initialized = FALSE;

    if (!initialized) {
        for (int i = 0; i < MAX_SOUNDS; i++)
        {
            snprintf(SoundInfos[i].alias, sizeof(SoundInfos[i].alias), "audio%d", i);
        }
        initialized = TRUE;
    }

    //判断当前的音效是否在循环播放
    int i;
    for (i = 0; i < MAX_SOUNDS; i++)
    {
        if (!SoundInfos[pCurrent].isLoop) {
            break;
        }
        pCurrent++;
        if (pCurrent >= MAX_SOUNDS) {
            pCurrent = 0;
        }
    }
    //如果所有音效均在循环播放中，则不进行音效生成
    if (i >= MAX_SOUNDS)    return NULL;

    SoundInfos[pCurrent].volume = 1.0f;

    // 打开并播放音效，使用定义好的别名
    char command[256];

    LoadSoundByAlias(filename, SoundInfos[pCurrent].alias);

    switch (type)
    {
    case AudioManager::AudioType::Music:
        SetVolume(SoundInfos[pCurrent].alias, MusicVolume);      //对wav不生效
        SoundInfos[pCurrent].type = AudioManager::AudioType::Music;
       // printf("MusicVolume:%d\r\n", MusicVolume);
        break;
    case AudioManager::AudioType::Effect:
        SetVolume(SoundInfos[pCurrent].alias, EffectVolume);      //对wav不生效
        SoundInfos[pCurrent].type = AudioManager::AudioType::Effect;
       // printf("EffectVolume:%d\r\n", EffectVolume);
        break;
    default:
        break;
    }

    // 播放音效
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", SoundInfos[pCurrent].alias);     //对wav不生效
    }
    else {
        snprintf(command, sizeof(command), "play %s", SoundInfos[pCurrent].alias);
    }
    mciSendStringA(command, NULL, 0, NULL);

    SoundInfos[pCurrent].isLoop = repeat;
    int index = pCurrent;
    pCurrent = (pCurrent + 1) % MAX_SOUNDS;

    return SoundInfos[index].alias;
}

const char* AudioManager::PlaySoundAudio(const char* filename, AudioType type, int volume, bool repeat)
{
    static bool initialized = FALSE;

    if (!initialized) {
        for (int i = 0; i < MAX_SOUNDS; i++)
        {
            snprintf(SoundInfos[i].alias, sizeof(SoundInfos[i].alias), "audio%d", i);
        }
        initialized = TRUE;
    }

    //判断当前的音效是否在循环播放
    int i;
    for (i = 0; i < MAX_SOUNDS; i++)
    {
        if (!SoundInfos[pCurrent].isLoop) {
            break;
        }
        pCurrent++;
        if (pCurrent >= MAX_SOUNDS) {
            pCurrent = 0;
        }
    }
    //如果所有音效均在循环播放中，则不进行音效生成
    if (i >= MAX_SOUNDS)    return NULL;

    SoundInfos[pCurrent].volume = 1.0f;

    // 打开并播放音效，使用定义好的别名
    char command[256];

    LoadSoundByAlias(filename, SoundInfos[pCurrent].alias);


    float f = (float)volume / 100.0f;
    SoundInfos[pCurrent].volume = f;
    switch (type)
    {
    case AudioManager::AudioType::Music:
       
        SetVolume(SoundInfos[pCurrent].alias, MusicVolume * f);      //对wav不生效
        SoundInfos[pCurrent].type = AudioManager::AudioType::Music;
        break;
    case AudioManager::AudioType::Effect:
        SetVolume(SoundInfos[pCurrent].alias, EffectVolume * f);      //对wav不生效
        SoundInfos[pCurrent].type = AudioManager::AudioType::Effect;
        break;
    default:
        break;
    }

    // 播放音效
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", SoundInfos[pCurrent].alias);     //对wav不生效
    }
    else {
        snprintf(command, sizeof(command), "play %s", SoundInfos[pCurrent].alias);
    }
    mciSendStringA(command, NULL, 0, NULL);

    SoundInfos[pCurrent].isLoop = repeat;
    int index = pCurrent;
    pCurrent = (pCurrent + 1) % MAX_SOUNDS;

    return SoundInfos[index].alias;
}


void AudioManager::StopSound(const char* alias,bool isClear)
{
    char command[256];

    // 检查字符串是否包含特定子字符串
    if (strstr(alias, "audio") != NULL) {
        int number = 0;
        // 提取子字符串后面的部分
        const char* numStr = alias + strlen("audio");
        if (*numStr != '\0') {
            // 将字符串转换为整数
            number = atoi(numStr);
            if (SoundInfos[number].isLoop)
                SoundInfos[number].isLoop = false;
        }
    }

    snprintf(command, sizeof(command), "stop %s", alias);
    mciSendStringA(command, NULL, 0, NULL);

    if (isClear)
    {
        snprintf(command, sizeof(command), "close %s", alias);
       // printf("%s\r\n", command);
        mciSendStringA(command, NULL, 0, NULL);
    }

}


void AudioManager::SetVolume(const char* alias, int volume)
{
    if (volume >= 100)
        volume = 100;
    else if (volume <= 0)
        volume = 0;
    // MCI 音量范围通常在 0 到 1000 之间
    char command[100];
    int mciVolume = volume * 10;
    sprintf_s(command, "setaudio %s volume to %d", alias, mciVolume);
    mciSendStringA(command, 0, 0, 0);
}


void AudioManager::SetMusicVolume(int volume)
{
    MusicVolume = volume;
    for (int i = 0; i < MAX_SOUNDS; i++)
    {
        if (!SoundInfos[i].isLoop || SoundInfos[i].type != AudioManager::AudioType::Music) {
            continue;
        }
        SetVolume(SoundInfos[i].alias, MusicVolume * SoundInfos[i].volume);      //对wav不生效
    }
}

void AudioManager::SetEffectVolume(int volume) 
{
    EffectVolume = volume;
    for (int i = 0; i < MAX_SOUNDS; i++)
    {
        if (SoundInfos[i].type != AudioManager::AudioType::Effect) {
            continue;
        }
        SetVolume(SoundInfos[i].alias, EffectVolume * SoundInfos[i].volume);      //对wav不生效
    }
}


void AudioManager::LoadSoundByAlias(const char* filename, const char* alias)
{
    char command[256];

    snprintf(command, sizeof(command), "stop %s", alias);
    mciSendStringA(command, NULL, 0, NULL);

    snprintf(command, sizeof(command), "close %s", alias);
    mciSendStringA(command, NULL, 0, NULL);

    snprintf(command, sizeof(command), "open %s alias %s", filename, alias);
    MCIERROR ret = mciSendStringA(command, NULL, 0, NULL);
    if (ret != 0)
    {
        TCHAR err[100] = { 0 };
        mciGetErrorString(ret, err, sizeof(err));
        printf("[open]:%s\r\n", err);
    }
}





