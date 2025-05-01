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
    // Character 쪽에서 이미지와 애니메이션 로딩 및 collider 초기화 다 처리됨
}

Player::~Player() = default;

void Player::Update()
{
    __super::Update();

    /*
    float deltaTime = TimeManager::Get().GetDeltaTime();
    Vector2 direction;

    if (InputManager::Get().IsKeyDown(VK_LEFT))  direction.x -= 1;
    if (InputManager::Get().IsKeyDown(VK_RIGHT)) direction.x += 1;
    if (InputManager::Get().IsKeyDown(VK_UP))    direction.y -= 1;
    if (InputManager::Get().IsKeyDown(VK_DOWN))  direction.y += 1;

    if (!direction.IsZero())
    {
        direction.Normalize();
        position += direction * speed * deltaTime;
    }

    // 경계 제한
    if (pBitmap)
    {
        int maxX = 1024 - pBitmap->GetWidth();
        int maxY = 768 - pBitmap->GetHeight();

        if (position.x < 0) position.x = 0;
        if (position.y < 0) position.y = 0;
        if (position.x > maxX) position.x = static_cast<float>(maxX);
        if (position.y > maxY) position.y = static_cast<float>(maxY);
    }
    */
    // Character::Update(); // 애니메이션 + 콜라이더 갱신
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