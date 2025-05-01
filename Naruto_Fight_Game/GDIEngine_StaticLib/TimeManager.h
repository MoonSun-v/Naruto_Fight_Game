#pragma once
#include "Singleton.h"

class TimeManager : public Singleton<TimeManager>
{
public:
	TimeManager() = default;
	~TimeManager() = default;
	void StartUp();
	void ShutDown();

	void Update();

	LARGE_INTEGER frequency;		// 성능 카운터 주파수 
	LARGE_INTEGER prevCounter;		// 이전 프레임 카운터 값
	LARGE_INTEGER currentCounter;	// 현재 프레임 카운터 값 
	LARGE_INTEGER intialCounter;	// 프로그램 시작된 초기 카운터 값 
	float deltaTime;				// 프레임간 시간 차이 

	float GetDeltaTime();
	float GetTotalTime();
};
