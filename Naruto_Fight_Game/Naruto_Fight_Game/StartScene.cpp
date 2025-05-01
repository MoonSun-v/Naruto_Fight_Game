#include "framework.h"
#include "StartScene.h"
#include "MainApp.h"

#include "../GDIEngine_StaticLib/SceneManager.h"
#include "../GDIEngine_StaticLib/InputManager.h"


void StartScene::Enter()
{
	__super::Enter();
}

void StartScene::Exit()
{
	__super::Exit();
}

void StartScene::Update()
{
	__super::Update();

	if (InputManager::Get().IsKeyPressed(VK_SPACE))
	{
		SceneManager::Get().ChangeScene(MainApp::SceneType::Scene_Map1);
	}
}

void StartScene::Render()
{
	__super::Render();

	RenderManager::Get().DrawText_w(L"StartScene", 10, 10, 30, Gdiplus::Color::Yellow);
}