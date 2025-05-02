#include "framework.h"
#include "Player.h"
#include "Idle_Player.h"

#include "../GDIEngine_StaticLib/TimeManager.h"
#include "../GDIEngine_StaticLib/InputManager.h"
#include "../GDIEngine_StaticLib/RenderManager.h"

#include <fstream>
#include <sstream>

Player::Player()
    : Character(L"../Resources/Naruto.png", L"../Resources/Animation/Naruto.txt")
{
    transparentColor = Gdiplus::Color(0, 128, 0); // 이미지 배경 투명 처리
    ChangeState(new Idle_Player());
}

Player::~Player() = default;

void Player::Update()
{
    __super::Update();

    float speed = 200.0f;
    float deltaTime = TimeManager::Get().GetDeltaTime();

    if (currentState)
        currentState->Update(this, deltaTime);
    
    // 화면 경계 제한 주기 

}

void Player::Render()
{
    __super::Render();

    RenderManager::Get().DrawText_w(
        L"Player Pos: " + std::to_wstring(position.x) + L", " + std::to_wstring(position.y),
        150, 10, 20, Gdiplus::Color::Blue);

    RenderManager::Get().DrawText_w(
        L"Collider Center: " + std::to_wstring(collider.m_Center.x) + L", " + std::to_wstring(collider.m_Center.y),
        150, 40, 20, Gdiplus::Color::Red);
}

void Player::ChangeState(PlayerState* newState)
{
    if (currentState)
    {
        currentState->Exit(this);
        delete currentState;
    }

    currentState = newState;

    if (currentState)
        currentState->Enter(this);
}

void Player::PlayAnimation(const std::wstring& name, bool force)
{
    animator.Play(name, force);
}
