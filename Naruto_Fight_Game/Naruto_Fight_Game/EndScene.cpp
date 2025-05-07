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

	m_StartSceneTimer = 0.0f;
}

void EndScene::Exit()
{
	__super::Exit();
}

void EndScene::Update()
{
	__super::Update();

	float deltaTime = TimeManager::Get().GetDeltaTime();

	m_StartSceneTimer += deltaTime;

	if (m_StartSceneTimer >= 5.0f) SceneManager::Get().ChangeScene(MainApp::SceneType::Scene_Start);
	 
	if (InputManager::Get().IsKeyPressed(VK_SPACE))  SceneManager::Get().ChangeScene(MainApp::SceneType::Scene_Start);
}

void EndScene::Render()
{
	__super::Render();

	RenderManager::Get().DrawText_w(L"전설은 이렇게 시작되었다.", 460, 250, 40, Gdiplus::Color::Black);
	RenderManager::Get().DrawText_w(L"그리고 짤로 남았다.", 500, 320, 35, Gdiplus::Color::Black);
}