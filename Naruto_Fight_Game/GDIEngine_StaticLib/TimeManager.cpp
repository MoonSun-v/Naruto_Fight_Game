#include "pch.h"
#include "TimeManager.h"

void TimeManager::StartUp()
{
	QueryPerformanceFrequency(&frequency);		// ���� Ÿ�̸Ӱ� 1�� ���� ������ų�� �ִ� TickCount ��
	QueryPerformanceCounter(&intialCounter);	// �ʱ� TickCount ��
	prevCounter = intialCounter;
}

void TimeManager::ShutDown()
{

}

void TimeManager::Update()
{
	QueryPerformanceCounter(&currentCounter); // ���� TickCount ��

	// ��Ÿ Ÿ�� ���: (���� ī���� - ���� ī����) / ���ļ�
	deltaTime = static_cast<float>(currentCounter.QuadPart - prevCounter.QuadPart) / static_cast<float>(frequency.QuadPart);  // ī�������̸� �ð� �ʴ����� ��ȯ

	prevCounter = currentCounter;
}


float TimeManager::GetDeltaTime()
{
	return deltaTime;
}

float TimeManager::GetTotalTime()
{
	return static_cast<float>(currentCounter.QuadPart - intialCounter.QuadPart) /
		static_cast<float>(frequency.QuadPart);  // ī�������̸� �ð� �ʴ����� ��ȯ
}
