#include "pch.h"
#include "SoundManager.h"

void SoundManager::StartUp()
{
    // FMOD 시스템 생성
    if (System_Create(&system) != FMOD_OK)
    {
        std::cerr << "[SoundManager] FMOD 시스템 생성 실패!" << std::endl;
        return;
    }

    if (system->init(512, FMOD_INIT_NORMAL, nullptr) != FMOD_OK)
    {
        std::cerr << "[SoundManager] FMOD 초기화 실패!" << std::endl;
        return;
    }
}

// BGM 

void SoundManager::PlayBGM(const char* filePath)
{
    // 이미 같은 BGM이 재생 중이면 무시
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

    // 루프 모드 설정
    system->createSound(filePath, FMOD_LOOP_NORMAL, nullptr, &bgm_sound);

    if (bgm_sound) 
    {
        bgm_sound->setMode(FMOD_LOOP_NORMAL);
        bgm_sound->setLoopCount(-1);
    }

    // 재생
    system->playSound(bgm_sound, nullptr, false, &bgm_channel);

    // 현재 경로 저장
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