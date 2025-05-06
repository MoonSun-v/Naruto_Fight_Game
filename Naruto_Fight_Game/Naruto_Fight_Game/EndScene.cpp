#include "framework.h"
#include "EndScene.h"
#include "MainApp.h"

#include "Background.h"

#include "../GDIEngine_StaticLib/SceneManager.h"
#include "../GDIEngine_StaticLib/InputManager.h"

void EndScene::Enter()
{
	__super::Enter();

	// 배경 객체 생성 
	Background* pBackground = CreateObject<Background>(L"../Resources/EndScene.png");
}

void EndScene::Exit()
{
	__super::Exit();
}

void EndScene::Update()
{
	__super::Update();
	 
	if (InputManager::Get().IsKeyPressed(VK_SPACE))  SceneManager::Get().ChangeScene(MainApp::SceneType::Scene_Start);
}

void EndScene::Render()
{
	__super::Render();

	// RenderManager::Get().DrawText_w(L"EndScene", 10, 10, 30, Gdiplus::Color::Yellow);
}