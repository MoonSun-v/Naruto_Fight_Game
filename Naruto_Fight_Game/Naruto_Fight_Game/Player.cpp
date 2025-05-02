#include "framework.h"
#include "Player.h"

#include "../GDIEngine_StaticLib/TimeManager.h"
#include "../GDIEngine_StaticLib/InputManager.h"
#include "../GDIEngine_StaticLib/RenderManager.h"

#include <fstream>
#include <sstream>

Player::Player()
    : Character(L"../Resources/Naruto.png", L"../Resources/Naruto/Naruto_Idle.txt")
{
    // 연두색 투명 처리
    transparentColor = Gdiplus::Color(0, 128, 0);

    // Character 쪽에서 이미지와 애니메이션 로딩 및 collider 초기화 다 처리됨
}

Player::~Player() = default;

void Player::Update()
{
    __super::Update();
    float speed = 200.0f;
    float deltaTime = TimeManager::Get().GetDeltaTime();

    if (InputManager::Get().IsKeyDown(VK_LEFT))     position.x -= speed * deltaTime;
    if (InputManager::Get().IsKeyDown(VK_RIGHT))    position.x += speed * deltaTime;
    if (InputManager::Get().IsKeyDown(VK_UP))       position.y -= speed * deltaTime;
    if (InputManager::Get().IsKeyDown(VK_DOWN))     position.y += speed * deltaTime;

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