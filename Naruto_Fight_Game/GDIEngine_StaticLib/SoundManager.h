#pragma once
#include "Singleton.h"

#include <Windows.h>
#include <fmod.hpp>
using namespace FMOD;

#pragma comment(lib, "fmod_vc.lib")

class SoundManager : public Singleton<SoundManager>
{
private:
	System* system = nullptr;
	Sound* bgm_sound = nullptr;
	Sound* sfx_sound = nullptr;
	Channel* bgm_channel = nullptr;
	Channel* sfx_channel = nullptr;

	std::string currentBGMPath; // ���� ��� ���� BGM ���� ���

public:
	SoundManager() = default;
	~SoundManager() = default;

	void StartUp();
	void ShutDown();

	void PlayBGM(const char* filePath);
	void StopBGM();
	void PlaySFX(const char* filePath);
	void StopSFX();
	void AllSoundStop();
};