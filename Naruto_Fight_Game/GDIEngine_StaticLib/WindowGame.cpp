#include "pch.h"
#include "WindowGame.h"

WindowGame::WindowGame(): m_hInstance(nullptr), m_hWnd(nullptr)
{
	m_pInstance = this;
}

WindowGame::~WindowGame()
{

}

WindowGame* WindowGame::m_pInstance = nullptr;


// [ ������ ���ν��� ] 
// 
// - �����츦 �����Ҷ� ������ Ŭ���� �ν��Ͻ��� ���� �ٸ��� �ִ�.
// - �ʱ� WM_NCCREATE ���� HWND�� �ν��Ͻ� �ּ� �����ϰ� -> �޼����� ������ ���� HWND�� ������ �ּҷ� MessageProc ȣ��.
//
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WindowGame* pThis = nullptr;

	if (uMsg == WM_NCCREATE) // WM_NCCREATE :������ ������ ���� ��. WM_CREATE���� ���� �߻�
	{
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam); // lParam�� CREATESTRUCT* 
		pThis = reinterpret_cast<WindowGame*>(cs->lpCreateParams);  // lpCreateParams : WindowGame�� this ������

		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)); // HWND�� this ������ ����
	}
	else 
	{
		pThis = reinterpret_cast<WindowGame*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)); // HWND�� �����ص� this �����͸� �����´�
	}

	// �� �ν��Ͻ��� �ڱ� �޽��� ó�� (��� �Լ� ȣ��)
	if (pThis) pThis->MessageProc(hwnd, uMsg, wParam, lParam);	

	return DefWindowProc(hwnd, uMsg, wParam, lParam);	
}


void WindowGame::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
}

void WindowGame::Initialize()
{
	char szPath[MAX_PATH] = { 0, };
	GetModuleFileNameA(NULL, szPath, MAX_PATH); // ���� ����� ���
	m_ModulePath = szPath;						// ��� ���
	GetCurrentDirectoryA(MAX_PATH, szPath);		// ���� �۾� ���丮
	m_WorkingPath = szPath;						// �۾� ���丮
	OutputDebugStringA(std::string(std::string(m_ModulePath) + std::string("\n")).c_str());
	OutputDebugStringA(std::string(std::string(m_WorkingPath) + std::string("\n")).c_str());

	m_hInstance = GetModuleHandle(NULL);		// ���� ���μ����� �ڵ�


	// [ WNDCLASSEX ����ü ���� ] -> RegisterClassEx
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = m_hInstance;
	wc.lpszClassName = m_WindowName.c_str();

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ���� ����
	RegisterClassEx(&wc);
	

	// ���ϴ� ũ�� �����Ǿ� ����
	SIZE clientSize = { m_Width, m_Height };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);


	// [ ������ �ν��Ͻ� ���� ] -> CreateWindowEx
	// �� �Լ��� ȣ��Ǹ� ���������� WindowProc ���� �� ȣ�� -> �� �� ���� ó�� �߻��ϴ� �޽����� WM_NCCREATE
	// 
	m_hWnd = CreateWindowEx(
		0,
		m_WindowName.c_str(),
		m_TitleName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, // �ʺ�, ����
		NULL,
		NULL,
		m_hInstance,
		this // lpCreateParams �� WM_NCCREATE �� ����
	);

	
	ShowWindow(m_hWnd, SW_SHOW); // ������ ȭ�鿡 ǥ��
	UpdateWindow(m_hWnd);        // ������ ���� 

	m_TimeManager.StartUp();
	m_InputManager.StartUp(m_hWnd);
	m_SoundManager.StartUp();
	m_RenderManager.StartUp(m_hWnd, m_Width, m_Height);
	m_SceneManager.StartUp();
}

void WindowGame::ShutDown()
{
	m_SceneManager.ShutDown();
	m_RenderManager.ShutDown(m_hWnd);
	m_SoundManager.ShutDown();
	m_TimeManager.ShutDown();
	m_InputManager.ShutDown();

	// Gdiplus::GdiplusShutdown(g_GdiPlusToken); // GDI+ ���� �� ���ҽ� ����
}

// [ �޽��� ���� ]
void WindowGame::Run()
{
	MSG msg = {};
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // PeekMessage �޼����� ������ true,������ false
		{
			if (msg.message == WM_QUIT) break;

			//������ �޽��� ó�� 
			TranslateMessage(&msg); // Ű�Է°��� �޽��� ��ȯ  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&msg);  // [ WindowProc ȣ�� ] : �޽����� ���� �츮�� ����� WindowGame::MessageProc()�� ����
		}
		Update();
		Render();
	}
}

void WindowGame::Update()
{
	m_TimeManager.Update(); 
	m_InputManager.Update();
	// m_SoundManager.Update();
	m_SceneManager.Update(); // ���� Scene�� �� Object�� Update�� ȣ��
}

void WindowGame::Render()
{
	m_RenderManager.BeginDraw(); //clear
	m_SceneManager.Render();     // ���� Scene�� �� Object�� Render�� ȣ��
	m_RenderManager.EndDraw(m_Width, m_Height); // bitblt copy
}