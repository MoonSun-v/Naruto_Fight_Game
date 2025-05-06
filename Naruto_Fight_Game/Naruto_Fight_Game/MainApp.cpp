#include "framework.h"
#include "MainApp.h"
#include "StartScene.h"
#include "Map1Scene.h"
#include "Map2Scene.h"
#include "Map3Scene.h"
#include "EndScene.h"

#include "../GDIEngine_StaticLib/SceneManager.h"


void MainApp::Initialize()
{
	__super::Initialize(); // WindowGame::Initialize()

	// �� ���� 
	SceneManager::Get().CreateScene<StartScene>();
	SceneManager::Get().CreateScene<Map1Scene>();
	// SceneManager::Get().CreateScene<Map2Scene>();
	// SceneManager::Get().CreateScene<Map3Scene>();
	SceneManager::Get().CreateScene<EndScene>();

	SceneManager::Get().ChangeScene(Scene_Start); // ó�� �� 
}

void MainApp::ShutDown()
{
	__super::ShutDown(); // WindowGame::Shutdown();
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