#include "framework.h"
#include "Run_Player.h"

#include "Jump_Player.h"
#include "Walk_Player.h"

#include "InputManager.h"
#include "Player.h"

void Run_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Run");
    player->moveSpeed = player->speed * 2.0f; // 달리기 속도
}

void Run_Player::Update(Player* player, float deltaTime)
{
    bool moved = false;

    if (InputManager::Get().IsKeyDown(VK_LEFT)) {
        player->SetFlipX(true);
    }

    if (InputManager::Get().IsKeyDown(VK_RIGHT)) {
        player->SetFlipX(false);
    }

    if (InputManager::Get().IsKeyDown(VK_LEFT)) {
        player->position.x -= player->moveSpeed * deltaTime;
        moved = true;
    }

    if (InputManager::Get().IsKeyDown(VK_RIGHT)) {
        player->position.x += player->moveSpeed * deltaTime;
        moved = true;
    }

    if (InputManager::Get().IsKeyDown(VK_UP)) {
        player->ChangeState(new Jump_Player(player->moveSpeed));
        return;
    }

    if (!moved) {
        player->ChangeState(new Walk_Player());
    }
}

void Run_Player::Exit(Player* player)
{
    // 특별한 정리 작업은 없음
}