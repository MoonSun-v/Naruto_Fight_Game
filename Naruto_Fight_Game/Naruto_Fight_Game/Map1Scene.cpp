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
#include "Die_Action_Player.h"
#include "Win_Action_Player.h"

void Map1Scene::Enter()
{
	__super::Enter();

	TimeManager::Get().StartUp();

    // 배경 객체 생성 (배경을 객체로 관리)
    Background* pBackground = CreateObject<Background>(L"../Resources/Map1_.png");

	// 플레이어 생성 및 초기 위치 설정
	player1 = CreateObject<Player>(
		L"../Resources/Naruto.png",
		L"../Resources/Animation/Naruto.txt"
	);
	player1->SetPosition(200.0f, 390.0f);
	player1->SetKeySet({ 'A', 'D', 'W', '1', '2', VK_LCONTROL }); // Left, Right, Up, Attack. Throw
    player1->transparentColor = Gdiplus::Color(0, 128, 0);

	player2 = CreateObject<Player>(
		L"../Resources/Sasuke.png",
		L"../Resources/Animation/New_Sasuke.txt"
	);
	player2->SetPosition(1000.0f, 390.0f);
	player2->SetKeySet({ VK_LEFT, VK_RIGHT, VK_UP, 'O', 'P', VK_RETURN });
    player2->transparentColor = Gdiplus::Color(141, 183, 230);

    player1->SetScale({ 1.3f, 1.3f });
    player2->SetScale({ 1.3f, 1.3f }); 
    player2->flipX = true;

    player1->SetStats(100, 100); 
    player2->SetStats(100, 100);


    // 초기화
    m_GameOver = false;
    m_EndSceneTimer = 0.0f;
    m_WaitingForSceneChange = false;
}

void Map1Scene::Exit()
{
	__super::Exit();
}

void Map1Scene::Update()
{
	__super::Update();

    float deltaTime = TimeManager::Get().GetDeltaTime();

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

    if (player1->IsSkill() && player1->m_AttackStartedThisFrame && m_SkillEffectImage == nullptr)
    {
        m_SkillEffectImage = new Gdiplus::Bitmap(L"../Resources/Naruto_Skill.png");
        m_SkillEffectTimer = 0.0f;
        m_SkillEffectOwner = SkillOwner::Player1;
    }

    if (player2->IsSkill() && player2->m_AttackStartedThisFrame && m_SkillEffectImage == nullptr)
    {
        m_SkillEffectImage = new Gdiplus::Bitmap(L"../Resources/Sasuke_Skill.png");
        m_SkillEffectTimer = 0.0f;
        m_SkillEffectOwner = SkillOwner::Player2;
    }
    if (m_SkillEffectImage)
    {
        m_SkillEffectTimer += deltaTime;
        if (m_SkillEffectTimer >= m_SkillEffectDuration)
        {
            delete m_SkillEffectImage;
            m_SkillEffectImage = nullptr;
            m_SkillEffectOwner = SkillOwner::None;
        }
    }

    // [ 게임 오버 ]
    if (!m_GameOver)
    {
        if (!player1->IsDead() && player2->IsDead())
        {
            player2->ChangeActionState(new Die_Action_Player());
            player1->ChangeActionState(new Win_Action_Player());
            OutputDebugString(L"플레이어 1 승리\n");
            m_GameOver = true;
            m_WaitingForSceneChange = true;
            m_EndSceneTimer = 0.0f; // 타이머 시작
        }
        else if (!player2->IsDead() && player1->IsDead())
        {
            player1->ChangeActionState(new Die_Action_Player());
            player2->ChangeActionState(new Win_Action_Player());
            OutputDebugString(L"플레이어 2 승리\n");
            m_GameOver = true;
            m_WaitingForSceneChange = true;
            m_EndSceneTimer = 0.0f; // 타이머 시작
        }
    }
    else if (m_WaitingForSceneChange)
    {
        m_EndSceneTimer += deltaTime;

        if (m_EndSceneTimer >= 5.0f)
        {
            SceneManager::Get().ChangeScene(MainApp::SceneType::Scene_End);
            m_WaitingForSceneChange = false;
        }
    }
}

void Map1Scene::Render()
{
	__super::Render();

    if (m_SkillEffectImage)
    {
        float x = 0.0f, y = 0.0f;

        if (m_SkillEffectOwner == SkillOwner::Player1)
        {
            x = 150.0f; y = 100.0f;
        }
        else if (m_SkillEffectOwner == SkillOwner::Player2)
        {
            x = 700.0f; y = 100.0f;
        }

        RenderManager::Get().DrawImage(m_SkillEffectImage, x, y);
    }

    // [ HP, MP 텍스트 ]
    RenderManager::Get().DrawText_w(std::to_wstring((int)player1->GetHP()), 110, 40, 20, Gdiplus::Color::Red);
    RenderManager::Get().DrawText_w(std::to_wstring((int)player1->GetMP()), 110, 80, 20, Gdiplus::Color::Blue);

    RenderManager::Get().DrawText_w(std::to_wstring((int)player2->GetHP()), WindowGame::Get().m_Width - 130, 40, 20, Gdiplus::Color::Red);
    RenderManager::Get().DrawText_w(std::to_wstring((int)player2->GetMP()), WindowGame::Get().m_Width - 130, 80, 20, Gdiplus::Color::Blue);

    // [ HP, MP Bar ]
    float hpBarWidth = 200.0f;
    float mpBarWidth = 200.0f;

    float player1HPRatio = player1->GetHP() / 100.0f;
    float player1MPRatio = player1->GetMP() / 100.0f;

    RenderManager::Get().DrawFilledRect(110, 25, hpBarWidth * player1HPRatio, 15, Gdiplus::Color::Red);
    RenderManager::Get().DrawFilledRect(110, 65, mpBarWidth * player1MPRatio, 15, Gdiplus::Color::Blue);

    // 오른쪽은 위치만 반대로
    float screenWidth = WindowGame::Get().m_Width;

    // Player2 HP
    float hpRatio2 = player2->GetHP() / 100.0f;
    float hpBarWidth2 = hpBarWidth * hpRatio2;
    RenderManager::Get().DrawFilledRect(screenWidth - 310 + (hpBarWidth - hpBarWidth2), 25, hpBarWidth2, 15, Gdiplus::Color::Red);

    // Player2 MP
    float mpRatio2 = player2->GetMP() / 100.0f;
    float mpBarWidth2 = mpBarWidth * mpRatio2;
    RenderManager::Get().DrawFilledRect(screenWidth - 310 + (mpBarWidth - mpBarWidth2), 65, mpBarWidth2, 15, Gdiplus::Color::Blue);


    // [ 조작키 ]
    RenderManager::Get().DrawText_w(L"A D             [이동]              <- ->", 500, 40, 15, Gdiplus::Color::Black);
    RenderManager::Get().DrawText_w(L"W               [점프]                  UP", 500, 70, 15, Gdiplus::Color::Black);
    RenderManager::Get().DrawText_w(L"1                [때리기]                O", 500, 100, 15, Gdiplus::Color::Black);
    RenderManager::Get().DrawText_w(L"2      [표창 던지기(MP-5)]     P", 500, 130, 15, Gdiplus::Color::Black);
    RenderManager::Get().DrawText_w(L"LCtrl     [스킬(MP-60)]     Enter   ", 500, 160, 15, Gdiplus::Color::Black);
}