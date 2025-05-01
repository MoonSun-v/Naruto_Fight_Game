#pragma once
#include "InputManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
// #include "SoundManager.h"
#include "RenderManager.h"
#include "Singleton.h"


// [ ������ ����, �޽��� ó��, ���� ���� ����, �׸��� ���� �Ŵ������� �ʱ�ȭ �� ������Ʈ ��� ]

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

	// ULONG_PTR g_GdiPlusToken; // GDI+ �ʱ�ȭ �� ���� �����ϴ� �ڵ�       

	// new�� �����ϸ� ���� h ������ ���漱���� �ذᰡ��
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
