#pragma once
#include "InputManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
// #include "SoundManager.h"
#include "RenderManager.h"
#include "Singleton.h"


// [ 윈도우 생성, 메시지 처리, 게임 루프 실행, 그리고 각종 매니저들의 초기화 및 업데이트 담당 ]

class WindowGame : public Singleton<WindowGame>
{
public:
	WindowGame();
	virtual ~WindowGame();
	static WindowGame* m_pInstance;

	int				m_Width = 1024;
	int				m_Height = 768;

private:
	HINSTANCE		m_hInstance;
	std::wstring	m_WindowName = L"GDIEngineWindowClass";
	std::wstring	m_TitleName = L"NARUTO_Fight_Game";
	std::string		m_ModulePath;
	std::string		m_WorkingPath;
	HWND			m_hWnd;

	// ULONG_PTR g_GdiPlusToken; // GDI+ 초기화 및 종료 관리하는 핸들       

	// new로 생성하면 여러 h 포함응 전방선언을 해결가능
	InputManager    m_InputManager;
	SceneManager    m_SceneManager;
	TimeManager     m_TimeManager;
	// SoundManager    m_SoundManager;
	RenderManager   m_RenderManager;

public:
	virtual void Initialize();
	virtual void ShutDown();
	virtual void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Run();

private:
	void Update();
	void Render();
};
