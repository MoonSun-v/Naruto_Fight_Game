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

	// 씬 생성 
	SceneManager::Get().CreateScene<StartScene>();
	SceneManager::Get().CreateScene<Map1Scene>();
	// SceneManager::Get().CreateScene<Map2Scene>();
	// SceneManager::Get().CreateScene<Map3Scene>();
	SceneManager::Get().CreateScene<EndScene>();

	SceneManager::Get().ChangeScene(Scene_Start); // 처음 씬 
}

void MainApp::ShutDown()
{
	__super::ShutDown(); // WindowGame::Shutdown();
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