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

    //�жϵ�ǰ����Ч�Ƿ���ѭ������
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
    //���������Ч����ѭ�������У��򲻽�����Ч����
    if (i >= MAX_SOUNDS)    return NULL;


    // �򿪲�������Ч��ʹ�ö���õı���
    char command[256];

    LoadSoundByAlias(filename, SoundInfos[pCurrent].alias);

    SetVolume(SoundInfos[pCurrent].alias, volume);      //��wav����Ч

    // ������Ч
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", SoundInfos[pCurrent].alias);     //��wav����Ч
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

    //�жϵ�ǰ����Ч�Ƿ���ѭ������
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
    //���������Ч����ѭ�������У��򲻽�����Ч����
    if (i >= MAX_SOUNDS)    return NULL;

    SoundInfos[pCurrent].volume = 1.0f;

    // �򿪲�������Ч��ʹ�ö���õı���
    char command[256];

    LoadSoundByAlias(filename, SoundInfos[pCurrent].alias);

  //  SetVolume(soundEffects[pCurrent].alias, AUDIO_VOLUM);      //��wav����Ч

    // ������Ч
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", SoundInfos[pCurrent].alias);     //��wav����Ч
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

    //�жϵ�ǰ����Ч�Ƿ���ѭ������
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
    //���������Ч����ѭ�������У��򲻽�����Ч����
    if (i >= MAX_SOUNDS)    return NULL;

    SoundInfos[pCurrent].volume = 1.0f;

    // �򿪲�������Ч��ʹ�ö���õı���
    char command[256];

    LoadSoundByAlias(filename, SoundInfos[pCurrent].alias);

    switch (type)
    {
    case AudioManager::AudioType::Music:
        SetVolume(SoundInfos[pCurrent].alias, MusicVolume);      //��wav����Ч
        SoundInfos[pCurrent].type = AudioManager::AudioType::Music;
       // printf("MusicVolume:%d\r\n", MusicVolume);
        break;
    case AudioManager::AudioType::Effect:
        SetVolume(SoundInfos[pCurrent].alias, EffectVolume);      //��wav����Ч
        SoundInfos[pCurrent].type = AudioManager::AudioType::Effect;
       // printf("EffectVolume:%d\r\n", EffectVolume);
        break;
    default:
        break;
    }

    // ������Ч
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", SoundInfos[pCurrent].alias);     //��wav����Ч
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

    //�жϵ�ǰ����Ч�Ƿ���ѭ������
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
    //���������Ч����ѭ�������У��򲻽�����Ч����
    if (i >= MAX_SOUNDS)    return NULL;

    SoundInfos[pCurrent].volume = 1.0f;

    // �򿪲�������Ч��ʹ�ö���õı���
    char command[256];

    LoadSoundByAlias(filename, SoundInfos[pCurrent].alias);


    float f = (float)volume / 100.0f;
    SoundInfos[pCurrent].volume = f;
    switch (type)
    {
    case AudioManager::AudioType::Music:
       
        SetVolume(SoundInfos[pCurrent].alias, MusicVolume * f);      //��wav����Ч
        SoundInfos[pCurrent].type = AudioManager::AudioType::Music;
        break;
    case AudioManager::AudioType::Effect:
        SetVolume(SoundInfos[pCurrent].alias, EffectVolume * f);      //��wav����Ч
        SoundInfos[pCurrent].type = AudioManager::AudioType::Effect;
        break;
    default:
        break;
    }

    // ������Ч
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", SoundInfos[pCurrent].alias);     //��wav����Ч
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

    // ����ַ����Ƿ�����ض����ַ���
    if (strstr(alias, "audio") != NULL) {
        int number = 0;
        // ��ȡ���ַ�������Ĳ���
        const char* numStr = alias + strlen("audio");
        if (*numStr != '\0') {
            // ���ַ���ת��Ϊ����
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
    // MCI ������Χͨ���� 0 �� 1000 ֮��
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
        SetVolume(SoundInfos[i].alias, MusicVolume * SoundInfos[i].volume);      //��wav����Ч
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
        SetVolume(SoundInfos[i].alias, EffectVolume * SoundInfos[i].volume);      //��wav����Ч
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





