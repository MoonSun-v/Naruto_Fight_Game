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


// [ 윈도우 프로시저 ] 
// 
// - 윈도우를 생성할때 설정한 클래스 인스턴스는 각각 다를수 있다.
// - 초기 WM_NCCREATE 에서 HWND에 인스턴스 주소 저장하고 -> 메세지를 받을때 마다 HWND에 설정된 주소로 MessageProc 호출.
//
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WindowGame* pThis = nullptr;

	if (uMsg == WM_NCCREATE) // WM_NCCREATE :윈도우 프레임 생성 전. WM_CREATE보다 이전 발생
	{
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam); // lParam은 CREATESTRUCT* 
		pThis = reinterpret_cast<WindowGame*>(cs->lpCreateParams);  // lpCreateParams : WindowGame의 this 포인터

		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)); // HWND에 this 포인터 저장
	}
	else 
	{
		pThis = reinterpret_cast<WindowGame*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)); // HWND에 저장해둔 this 포인터를 가져온다
	}

	// 각 인스턴스가 자기 메시지 처리 (멤버 함수 호출)
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
	GetModuleFileNameA(NULL, szPath, MAX_PATH); // 현재 모듈의 경로
	m_ModulePath = szPath;						// 모듈 경로
	GetCurrentDirectoryA(MAX_PATH, szPath);		// 현재 작업 디렉토리
	m_WorkingPath = szPath;						// 작업 디렉토리
	OutputDebugStringA(std::string(std::string(m_ModulePath) + std::string("\n")).c_str());
	OutputDebugStringA(std::string(std::string(m_WorkingPath) + std::string("\n")).c_str());

	m_hInstance = GetModuleHandle(NULL);		// 현재 프로세스의 핸들


	// [ WNDCLASSEX 구조체 설정 ] -> RegisterClassEx
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = m_hInstance;
	wc.lpszClassName = m_WindowName.c_str();

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 배경색 설정
	RegisterClassEx(&wc);
	

	// 원하는 크기 조정되어 리턴
	SIZE clientSize = { m_Width, m_Height };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);


	// [ 윈도우 인스턴스 생성 ] -> CreateWindowEx
	// 이 함수가 호출되면 내부적으로 WindowProc 여러 번 호출 -> 그 중 가장 처음 발생하는 메시지가 WM_NCCREATE
	// 
	m_hWnd = CreateWindowEx(
		0,
		m_WindowName.c_str(),
		m_TitleName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, // 너비, 높이
		NULL,
		NULL,
		m_hInstance,
		this // lpCreateParams → WM_NCCREATE 에 전달
	);

	
	ShowWindow(m_hWnd, SW_SHOW); // 윈도우 화면에 표시
	UpdateWindow(m_hWnd);        // 윈도우 갱신 

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

	// Gdiplus::GdiplusShutdown(g_GdiPlusToken); // GDI+ 종료 및 리소스 해제
}

// [ 메시지 루프 ]
void WindowGame::Run()
{
	MSG msg = {};
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // PeekMessage 메세지가 있으면 true,없으면 false
		{
			if (msg.message == WM_QUIT) break;

			//윈도우 메시지 처리 
			TranslateMessage(&msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&msg);  // [ WindowProc 호출 ] : 메시지에 따라 우리가 등록한 WindowGame::MessageProc()로 연결
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
	m_SceneManager.Update(); // 현재 Scene이 각 Object의 Update를 호출
}

void WindowGame::Render()
{
	m_RenderManager.BeginDraw(); //clear
	m_SceneManager.Render();     // 현재 Scene이 각 Object의 Render를 호출
	m_RenderManager.EndDraw(m_Width, m_Height); // bitblt copy
}