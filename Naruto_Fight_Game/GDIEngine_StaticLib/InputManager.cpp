#include "pch.h"
#include "InputManager.h"

void InputManager::StartUp(HWND hWnd)
{
	m_hWnd = hWnd; // ������ �ڵ�
}

void InputManager::Update()
{
	// ���콺 ��ǥ
	::GetCursorPos(&m_mouseClient);
	::ScreenToClient(m_hWnd, &m_mouseClient);

	// ���� �������� Ű ���¸� ���� ���·� ���� 
	memcpy_s(m_prevState, sizeof(m_prevState), m_currState, sizeof(m_currState));
	for (int i = 0; i < 256; i++) { // ���� Ű ���� ���� 
		m_currState[i] = GetAsyncKeyState(i);
	}
}

// [ Ű�� ��� ������ �ִ� ���� ]
bool InputManager::IsKeyDown(int vKey)
{
	return (m_currState[vKey] & 0x8000) != 0;
}

// [ Ű�� �̹� �����ӿ� ó�� ���� : �����Ӹ� true ]
bool InputManager::IsKeyPressed(int vKey)
{
	return (!(m_prevState[vKey] & 0x8000) && (m_currState[vKey] & 0x8000));
}

// [ Ű�� �̹� �����ӿ� ������ : �� �����Ӹ� true ] 
bool InputManager::IsKeyReleased(int vKey)
{
	return ((m_prevState[vKey] & 0x8000) && !(m_currState[vKey] & 0x8000));
}
