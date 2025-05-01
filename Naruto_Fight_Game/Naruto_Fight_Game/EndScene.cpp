#include "framework.h"
#include "EndScene.h"
#include "MainApp.h"

#include "../GDIEngine_StaticLib/SceneManager.h"
#include "../GDIEngine_StaticLib/InputManager.h"

void EndScene::Enter()
{
	__super::Enter();
}

void EndScene::Exit()
{
	__super::Exit();
}

void EndScene::Update()
{
	__super::Update();

	if (InputManager::Get().IsKeyPressed(VK_SPACE)) // 单捞磐 秦力 贸府 镭瘤 富鲤! 
	{
		SceneManager::Get().ChangeScene(MainApp::SceneType::Scene_Start);
	}
}

void EndScene::Render()
{
	__super::Render();

	RenderManager::Get().DrawText_w(L"EndScene", 10, 10, 30, Gdiplus::Color::Yellow);
}