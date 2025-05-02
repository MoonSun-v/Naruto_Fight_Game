#include "framework.h"
#include "Player.h"
#include "Idle_Player.h"
#include "Run_Player.h"
#include "Attack_Action.h"

#include "Idle_Action.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "RenderManager.h"

#include <fstream>
#include <sstream>

Player::Player()
    : Character(L"../Resources/Naruto.png", L"../Resources/Animation/Naruto.txt")
{
    transparentColor = Gdiplus::Color(0, 128, 0); // �̹��� ��� ���� ó��
    ChangeMoveState(new Idle_Player());
    ChangeActionState(new Idle_Action());
}

Player::~Player() = default;

void Player::Update()
{
    __super::Update();

    float currentTime = TimeManager::Get().GetTotalTime();

    // ���� �켱 ó��
    if (InputManager::Get().IsKeyPressed('D')) {
        ChangeActionState(new Attack_Action());
        return;
    }

    // [ ����Ű ������ ���� ]
    if (InputManager::Get().IsKeyPressed(VK_LEFT)) {
        if (lastKeyPressed == VK_LEFT && (currentTime - lastKeyTime) < doubleTapThreshold) {
            ChangeMoveState(new Run_Player());
            return;
        }
        lastKeyPressed = VK_LEFT;
        lastKeyTime = currentTime;
    }
    if (InputManager::Get().IsKeyPressed(VK_RIGHT)) {
        if (lastKeyPressed == VK_RIGHT && (currentTime - lastKeyTime) < doubleTapThreshold) {
            ChangeMoveState(new Run_Player());
            return;
        }
        lastKeyPressed = VK_RIGHT;
        lastKeyTime = currentTime;
    }
    
    if (moveState) moveState->Update(this, TimeManager::Get().GetDeltaTime());
    if (actionState) actionState->Update(this, TimeManager::Get().GetDeltaTime());
    
    // [ ȭ�� ��� ���� �ֱ� ]
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

void Player::ChangeMoveState(PlayerState* newState) 
{
    if (moveState) moveState->Exit(this);
    delete moveState;
    moveState = newState;
    if (moveState) moveState->Enter(this);
}

void Player::ChangeActionState(ActionState* newState) 
{
    if (actionState) actionState->Exit(this);
    delete actionState;
    actionState = newState;
    if (actionState) actionState->Enter(this);
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
