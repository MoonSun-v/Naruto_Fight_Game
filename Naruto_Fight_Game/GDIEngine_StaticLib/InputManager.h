#pragma once
#include "Singleton.h"

class InputManager : public Singleton<InputManager>
{
public:
	InputManager() = default;	// 다른 생성을 통한 생성자 호출은 금지
	~InputManager() = default;

	HWND m_hWnd;			// 윈도우 핸들
	POINT m_mouseClient;	// 마우스 좌표
	SHORT m_prevState[256] = { 0 };
	SHORT m_currState[256] = { 0 };

public:
	void StartUp(HWND hWnd);
	void ShutDown() {};

	void Update();

	bool IsKeyDown(int vKey);
	bool IsKeyPressed(int vKey);
	bool IsKeyReleased(int vKey);
};