#include "framework.h"
#include "StartScene.h"
#include "MainApp.h"

#include "Background.h"

#include "../GDIEngine_StaticLib/SceneManager.h"
#include "../GDIEngine_StaticLib/InputManager.h"


void StartScene::Enter()
{
	__super::Enter();

	// 배경 객체 생성 
	Background* pBackground = CreateObject<Background>(L"../Resources/StartScene.png");

	StartTitle = new Gdiplus::Bitmap(L"../Resources/Start_Title.png");

}

void StartScene::Exit()
{
	__super::Exit();
}

void StartScene::Update()
{
	__super::Update();

	if (InputManager::Get().IsKeyPressed(VK_SPACE)) SceneManager::Get().ChangeScene(MainApp::SceneType::Scene_Map1);
}

void StartScene::Render()
{
	__super::Render();

	RenderManager::Get().DrawImage(StartTitle, 80.0f, 70.0f);

	RenderManager::Get().DrawText_w(L"나루토 vs 사스케", 485, 255, 35, Gdiplus::Color::Black);
	RenderManager::Get().DrawText_w(L"가슴이 웅장해지는 결투", 500, 300, 20, Gdiplus::Color::Black);
	RenderManager::Get().DrawText_w(L"<< 시작하려면 < SpaceBar > 누르세요 >>", 440, 400, 20, Gdiplus::Color::Black);
}