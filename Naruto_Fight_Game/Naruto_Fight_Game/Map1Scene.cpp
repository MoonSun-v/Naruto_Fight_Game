#include "framework.h"
#include "Map1Scene.h"
#include "MainApp.h"

#include "Player.h"
#include "Weapon.h"
#include "Background.h"

#include "../GDIEngine_StaticLib/SceneManager.h"
#include "../GDIEngine_StaticLib/InputManager.h"
#include "../GDIEngine_StaticLib/TimeManager.h"

#include "Hurt_Action_Player.h"

void Map1Scene::Enter()
{
	__super::Enter();

	TimeManager::Get().StartUp();

    // 배경 객체 생성 (배경을 객체로 관리)
    Background* pBackground = CreateObject<Background>(L"../Resources/Map1.png");


	// 플레이어 생성 및 초기 위치 설정
	Player* player1 = CreateObject<Player>(
		L"../Resources/Naruto.png",
		L"../Resources/Animation/Naruto.txt"
	);
	player1->SetPosition(60.0f, 400.0f);
	player1->SetKeySet({ 'A', 'D', 'W', '1', '2' }); // Left, Right, Up, Attack. Throw

	Player* player2 = CreateObject<Player>(
		L"../Resources/Sasuke_ver.png",
		L"../Resources/Animation/Sasuke.txt"
	);
	player2->SetPosition(700.0f, 400.0f);
	player2->SetKeySet({ VK_LEFT, VK_RIGHT, VK_UP, 'O', 'P' });

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

    // ------- 공격 충돌 체크 ----------

    Player* player1 = nullptr;
    Player* player2 = nullptr;

    // 플레이어 객체 가져오기
    for (Object* obj : m_Objects)
    {
        if (Player* p = dynamic_cast<Player*>(obj))
        {
            if (!player1) player1 = p;
            else player2 = p;
        }
    }

    if (!player1 || !player2) return;

    // 플레이어 1이 공격 중일 때
    if (player1->IsAttacking() && player1->m_AttackStartedThisFrame && !player2->IsHurt())
    {
        if (player1->GetAABB().CheckIntersect(player2->GetAABB()))
        {
            if (!player1->m_HasHitThisAttack && !player1->m_HasCollidedWithTarget)
            {
                player2->ChangeActionState(new Hurt_Action_Player());
                player1->m_HasHitThisAttack = true;
            }
            player1->m_HasCollidedWithTarget = true;
        }
        else
        {
            player1->m_HasCollidedWithTarget = false;
            player1->m_HasHitThisAttack = false;
        }
    }

    // 플레이어 2가 공격 중일 때
    if (player2->IsAttacking() && player2->m_AttackStartedThisFrame && !player1->IsHurt())
    {
        if (player2->GetAABB().CheckIntersect(player1->GetAABB()))
        {
            if (!player2->m_HasHitThisAttack && !player2->m_HasCollidedWithTarget)
            {
                player1->ChangeActionState(new Hurt_Action_Player());
                player2->m_HasHitThisAttack = true;
            }
            player2->m_HasCollidedWithTarget = true;
        }
        else
        {
            player2->m_HasCollidedWithTarget = false;
            player2->m_HasHitThisAttack = false;
        }
    }
}

void Map1Scene::Render()
{
	__super::Render();

	RenderManager::Get().DrawText_w(L"Map1Scene", 10, 10, 30, Gdiplus::Color::Yellow);
}