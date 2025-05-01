#include "framework.h"
#include "Map1Scene.h"
#include "MainApp.h"

#include "Player.h"

#include "../GDIEngine_StaticLib/SceneManager.h"
#include "../GDIEngine_StaticLib/InputManager.h"
#include "../GDIEngine_StaticLib/TimeManager.h"

void Map1Scene::Enter()
{
	__super::Enter();

	TimeManager::Get().StartUp();

	// �÷��̾� ���� �� �ʱ� ��ġ ����
	Player* pPlayer = (Player*)CreateObject<Player>();
	pPlayer->SetPosition( 60.0f, 60.0f );  // ������ ��ġ�� ����
}

void Map1Scene::Exit()
{
	__super::Exit();
}

void Map1Scene::Update()
{
	__super::Update();

	if (InputManager::Get().IsKeyPressed(VK_SPACE))
	{
		SceneManager::Get().ChangeScene(MainApp::SceneType::Scene_Map2);
	}
}

void Map1Scene::Render()
{
	__super::Render();

	RenderManager::Get().DrawText_w(L"Map1Scene", 10, 10, 30, Gdiplus::Color::Yellow);
}