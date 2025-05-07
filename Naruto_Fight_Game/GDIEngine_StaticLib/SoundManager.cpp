#include "pch.h"
#include "SoundManager.h"

void SoundManager::StartUp()
{
    // FMOD �ý��� ����
    if (System_Create(&system) != FMOD_OK)
    {
        std::cerr << "[SoundManager] FMOD �ý��� ���� ����!" << std::endl;
        return;
    }

    if (system->init(512, FMOD_INIT_NORMAL, nullptr) != FMOD_OK)
    {
        std::cerr << "[SoundManager] FMOD �ʱ�ȭ ����!" << std::endl;
        return;
    }
}

// BGM 

void SoundManager::PlayBGM(const char* filePath)
{
    // �̹� ���� BGM�� ��� ���̸� ����
    if (currentBGMPath == filePath && bgm_channel != nullptr)
    {
        bool isPlaying = false;
        bgm_channel->isPlaying(&isPlaying);
        if (isPlaying) return; 
    }

    if (bgm_sound) 
    {
        bgm_sound->release();
        bgm_sound = nullptr;
    }

    // ���� ��� ����
    system->createSound(filePath, FMOD_LOOP_NORMAL, nullptr, &bgm_sound);

    if (bgm_sound) 
    {
        bgm_sound->setMode(FMOD_LOOP_NORMAL);
        bgm_sound->setLoopCount(-1);
    }

    // ���
    system->playSound(bgm_sound, nullptr, false, &bgm_channel);

    // ���� ��� ����
    currentBGMPath = filePath;
}

void SoundManager::StopBGM()
{
    if (bgm_channel) bgm_channel->stop();
}

// SFX 

void SoundManager::PlaySFX(const char* filePath)
{
    if (sfx_sound) {
        sfx_sound->release();
        sfx_sound = nullptr;
    }

    system->createSound(filePath, FMOD_DEFAULT, nullptr, &sfx_sound);
    system->playSound(sfx_sound, nullptr, false, &sfx_channel);
}

void SoundManager::StopSFX()
{
    if (sfx_channel)sfx_channel->stop();
}

void SoundManager::AllSoundStop()
{
    if (bgm_channel) {
        bgm_channel->stop();
    }

    if (sfx_channel) {
        sfx_channel->stop();
    }
}

void SoundManager::ShutDown()
{
    if (bgm_sound)
    {
        bgm_sound->release();
        bgm_sound = nullptr;
    }

    if (sfx_sound)
    {
        sfx_sound->release();
        sfx_sound = nullptr;
    }

    if (system)
    {
        system->close();
        system->release();
        system = nullptr;
    }
}