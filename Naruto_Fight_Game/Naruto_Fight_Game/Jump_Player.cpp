#include "framework.h"
#include "Jump_Player.h"
#include "Player.h"
#include "Idle_Player.h"

void Jump_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Jump", true);
    jumpTime = 0.0f;
    startY = player->position.y;
}

void Jump_Player::Update(Player* player, float deltaTime)
{
    jumpTime += deltaTime;

    // 간단한 점프 파라볼라 (sin 곡선 활용)
    float t = jumpTime / duration;
    if (t >= 1.0f) {
        player->position.y = startY;
        player->ChangeState(new Idle_Player());
        return;
    }

    float jumpOffset = sinf(t * 3.14159f) * jumpHeight;
    player->position.y = startY - jumpOffset;
}

void Jump_Player::Exit(Player* player)
{
    player->position.y = startY; // 위치 정리
}