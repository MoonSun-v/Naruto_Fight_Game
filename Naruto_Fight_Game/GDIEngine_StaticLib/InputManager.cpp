#include "pch.h"
#include "InputManager.h"

void InputManager::StartUp(HWND hWnd)
{
	m_hWnd = hWnd; // 윈도우 핸들
}

void InputManager::Update()
{
	// 마우스 좌표
	::GetCursorPos(&m_mouseClient);
	::ScreenToClient(m_hWnd, &m_mouseClient);

	// 이전 프레임의 키 상태를 현재 상태로 복사 
	memcpy_s(m_prevState, sizeof(m_prevState), m_currState, sizeof(m_currState));
	for (int i = 0; i < 256; i++) { // 현재 키 상태 갱신 
		m_currState[i] = GetAsyncKeyState(i);
	}
}

// [ 키가 계속 눌리고 있는 상태 ]
bool InputManager::IsKeyDown(int vKey)
{
	return (m_currState[vKey] & 0x8000) != 0;
}

// [ 키가 이번 프레임에 처음 눌림 : 프레임만 true ]
bool InputManager::IsKeyPressed(int vKey)
{
	return (!(m_prevState[vKey] & 0x8000) && (m_currState[vKey] & 0x8000));
}

// [ 키가 이번 프레임에 떼졌음 : 한 프레임만 true ] 
bool InputManager::IsKeyReleased(int vKey)
{
	return ((m_prevState[vKey] & 0x8000) && !(m_currState[vKey] & 0x8000));
}
