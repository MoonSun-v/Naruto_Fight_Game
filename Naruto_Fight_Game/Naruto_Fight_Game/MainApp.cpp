#include "framework.h"
#include "MainApp.h"
// #include "MenuScene.h"
// #include "PlayScene.h"
// #include "EndScene.h"

// #include "../GDIEngine_StaticLib/SceneManager.h"


void MainApp::Initialize()
{
	__super::Initialize(); // WindowGame::Initialize()

	// 씬 생성 
	// SceneManager::Get().CreateScene<MenuScene>();
	// SceneManager::Get().CreateScene<PlayScene>();
	// SceneManager::Get().CreateScene<EndScene>();

	// SceneManager::Get().ChangeScene(Scene_Menu); // 처음엔 메뉴 씬부터 시작
}

void MainApp::ShutDown()
{
	__super::ShutDown(); //  WindowGame::Shutdown();
}

void MainApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	__super::MessageProc(hwnd, uMsg, wParam, lParam); // WM_DESTROY 기본처리

	// MainGameApp에서만 처리하고싶은 내용
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	}
}