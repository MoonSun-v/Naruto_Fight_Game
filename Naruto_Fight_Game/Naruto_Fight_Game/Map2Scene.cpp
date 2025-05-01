#include "framework.h"
#include "Map2Scene.h"
#include "MainApp.h"

#include "../GDIEngine_StaticLib/SceneManager.h"
#include "../GDIEngine_StaticLib/InputManager.h"

void Map2Scene::Enter()
{
	__super::Enter();
}

void Map2Scene::Exit()
{
	__super::Exit();
}

void Map2Scene::Update()
{
	__super::Update();

	if (InputManager::Get().IsKeyPressed(VK_SPACE))
	{
		SceneManager::Get().ChangeScene(MainApp::SceneType::Scene_Map3);
	}
}

void Map2Scene::Render()
{
	__super::Render();

	RenderManager::Get().DrawText_w(L"Map2Scene", 10, 10, 30, Gdiplus::Color::Yellow);
}