#include "framework.h"
#include "Player.h"
#include "Idle_Player.h"
#include "Run_Player.h"
#include "Attack_Player.h"

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

    float currentTime = TimeManager::Get().GetTotalTime();

    // 공격 우선 처리
    if (InputManager::Get().IsKeyPressed('D')) {
        ChangeState(new Attack_Player());
        return;
    }

    // [ 방향키 더블탭 감지 ]
    if (InputManager::Get().IsKeyPressed(VK_LEFT)) {
        if (lastKeyPressed == VK_LEFT && (currentTime - lastKeyTime) < doubleTapThreshold) {
            ChangeState(new Run_Player());
            return;
        }
        lastKeyPressed = VK_LEFT;
        lastKeyTime = currentTime;
    }
    if (InputManager::Get().IsKeyPressed(VK_RIGHT)) {
        if (lastKeyPressed == VK_RIGHT && (currentTime - lastKeyTime) < doubleTapThreshold) {
            ChangeState(new Run_Player());
            return;
        }
        lastKeyPressed = VK_RIGHT;
        lastKeyTime = currentTime;
    }
    
    if (currentState) currentState->Update(this, TimeManager::Get().GetDeltaTime());
    
    // [ 화면 경계 제한 주기 ]
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

    RenderManager::Get().DrawText_w(
        L"moveSpeed: " + std::to_wstring(moveSpeed), 150, 80, 20, Gdiplus::Color::Green);
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

void Player::ResetRunInput()
{
    lastKeyPressed = 0;
    lastKeyTime = 0.0f;
}
