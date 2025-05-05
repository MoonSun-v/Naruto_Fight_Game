#include "framework.h"
#include "Map1Scene.h"
#include "MainApp.h"

#include "Player.h"
#include "Weapon.h"

#include "../GDIEngine_StaticLib/SceneManager.h"
#include "../GDIEngine_StaticLib/InputManager.h"
#include "../GDIEngine_StaticLib/TimeManager.h"

#include "Hurt_Action_Player.h"

void Map1Scene::Enter()
{
	__super::Enter();

	TimeManager::Get().StartUp();

	// 플레이어 생성 및 초기 위치 설정
	Player* player1 = CreateObject<Player>(
		L"../Resources/Naruto.png",
		L"../Resources/Animation/Naruto.txt"
	);
	player1->SetPosition(60.0f, 400.0f);
	player1->SetKeySet({ 'A', 'D', 'W', '1', '2' }); // Left, Right, Up, Attack. Throw

	Player* player2 = CreateObject<Player>(
		L"../Resources/Sasuke.png",
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

    Player* player1 = nullptr;
    Player* player2 = nullptr;

    // 플레이어 객체 가져오기 (추적 방법에 따라 수정 필요)
    for (Object* obj : m_Objects)
    {
        if (Player* p = dynamic_cast<Player*>(obj))
        {
            if (!player1) player1 = p;
            else player2 = p;
        }
    }

    if (!player1 || !player2) return;

    // 둘 다 공격 중일 때
    if (player1->IsAttacking() && player2->IsAttacking())
    {
        if (player1->GetAABB().CheckIntersect(player2->GetAABB()))
        {
            float time1 = player1->GetAnimator().GetElapsedTime();
            float time2 = player2->GetAnimator().GetElapsedTime();

            if (fabs(time1 - time2) < 0.1f)  // 거의 동시에 공격
            {
                player1->ChangeActionState(new Hurt_Action_Player());
                player2->ChangeActionState(new Hurt_Action_Player());
            }
            else if (time1 < time2)
            {
                player2->ChangeActionState(new Hurt_Action_Player());
            }
            else
            {
                player1->ChangeActionState(new Hurt_Action_Player());
            }
        }
    }
    // 한쪽만 공격 중일 때
    else if (player1->IsAttacking() && !player2->IsHurt())
    {
        if (player1->GetAABB().CheckIntersect(player2->GetAABB()))
        {
            player2->ChangeActionState(new Hurt_Action_Player());
        }
    }
    else if (player2->IsAttacking() && !player1->IsHurt())
    {
        if (player2->GetAABB().CheckIntersect(player1->GetAABB()))
        {
            player1->ChangeActionState(new Hurt_Action_Player());
        }
    }
}

void Map1Scene::Render()
{
	__super::Render();

	RenderManager::Get().DrawText_w(L"Map1Scene", 10, 10, 30, Gdiplus::Color::Yellow);
}