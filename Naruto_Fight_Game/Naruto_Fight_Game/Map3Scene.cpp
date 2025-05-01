#include "framework.h"
#include "Map3Scene.h"
#include "MainApp.h"

#include "../GDIEngine_StaticLib/SceneManager.h"
#include "../GDIEngine_StaticLib/InputManager.h"

void Map3Scene::Enter()
{
	__super::Enter();
}

void Map3Scene::Exit()
{
	__super::Exit();
}

void Map3Scene::Update()
{
	__super::Update();

	if (InputManager::Get().IsKeyPressed(VK_SPACE))
	{
		SceneManager::Get().ChangeScene(MainApp::SceneType::Scene_End);
	}
}

void Map3Scene::Render()
{
	__super::Render();

	RenderManager::Get().DrawText_w(L"Map3Scene", 10, 10, 30, Gdiplus::Color::Yellow);
}