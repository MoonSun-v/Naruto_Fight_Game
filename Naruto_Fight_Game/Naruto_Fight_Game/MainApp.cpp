#include "framework.h"
#include "MainApp.h"
// #include "MenuScene.h"
// #include "PlayScene.h"
// #include "EndScene.h"

// #include "../GDIEngine_StaticLib/SceneManager.h"


void MainApp::Initialize()
{
	__super::Initialize(); // WindowGame::Initialize()

	// �� ���� 
	// SceneManager::Get().CreateScene<MenuScene>();
	// SceneManager::Get().CreateScene<PlayScene>();
	// SceneManager::Get().CreateScene<EndScene>();

	// SceneManager::Get().ChangeScene(Scene_Menu); // ó���� �޴� ������ ����
}

void MainApp::ShutDown()
{
	__super::ShutDown(); //  WindowGame::Shutdown();
}

void MainApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	__super::MessageProc(hwnd, uMsg, wParam, lParam); // WM_DESTROY �⺻ó��

	// MainGameApp������ ó���ϰ���� ����
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	}
}