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

	LARGE_INTEGER frequency;		// ���� ī���� ���ļ� 
	LARGE_INTEGER prevCounter;		// ���� ������ ī���� ��
	LARGE_INTEGER currentCounter;	// ���� ������ ī���� �� 
	LARGE_INTEGER intialCounter;	// ���α׷� ���۵� �ʱ� ī���� �� 
	float deltaTime;				// �����Ӱ� �ð� ���� 

	float GetDeltaTime();
	float GetTotalTime();
};
