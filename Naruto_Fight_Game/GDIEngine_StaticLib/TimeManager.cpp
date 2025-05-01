#include "pch.h"
#include "TimeManager.h"

void TimeManager::StartUp()
{
	QueryPerformanceFrequency(&frequency);		// 고성능 타이머가 1초 동안 증가시킬수 있는 TickCount 값
	QueryPerformanceCounter(&intialCounter);	// 초기 TickCount 값
	prevCounter = intialCounter;
}

void TimeManager::ShutDown()
{

}

void TimeManager::Update()
{
	QueryPerformanceCounter(&currentCounter); // 현재 TickCount 값

	// 델타 타임 계산: (현재 카운터 - 이전 카운터) / 주파수
	deltaTime = static_cast<float>(currentCounter.QuadPart - prevCounter.QuadPart) / static_cast<float>(frequency.QuadPart);  // 카운터차이를 시간 초단위로 변환

	prevCounter = currentCounter;
}


float TimeManager::GetDeltaTime()
{
	return deltaTime;
}

float TimeManager::GetTotalTime()
{
	return static_cast<float>(currentCounter.QuadPart - intialCounter.QuadPart) /
		static_cast<float>(frequency.QuadPart);  // 카운터차이를 시간 초단위로 변환
}
