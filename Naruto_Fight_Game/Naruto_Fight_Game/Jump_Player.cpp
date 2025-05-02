#include "framework.h"
#include "Jump_Player.h"

#include "Idle_Player.h"

#include "InputManager.h"
#include "Player.h"

Jump_Player::Jump_Player(float initialSpeed) : horizontalSpeed(initialSpeed)
{
}

void Jump_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Jump", true);
    jumpTime = 0.0f;
    startY = player->position.y;
}

void Jump_Player::Update(Player* player, float deltaTime)
{
    jumpTime += deltaTime;

    // 간단한 점프 곡선 (sin 파라볼라)
    float t = jumpTime / duration;
    if (t >= 1.0f) {
        player->position.y = startY;
        player->ChangeMoveState(new Idle_Player());
        return;
    }

    float jumpOffset = sinf(t * 3.14159f) * jumpHeight;
    player->position.y = startY - jumpOffset;

    // 점프 중 좌우 이동
    if (InputManager::Get().IsKeyDown(VK_LEFT)) {
        player->position.x -= horizontalSpeed * deltaTime;
        player->SetFlipX(true);
    }

    if (InputManager::Get().IsKeyDown(VK_RIGHT)) {
        player->position.x += horizontalSpeed * deltaTime;
        player->SetFlipX(false);
    }
}

void Jump_Player::Exit(Player* player)
{
    player->position.y = startY; 
}