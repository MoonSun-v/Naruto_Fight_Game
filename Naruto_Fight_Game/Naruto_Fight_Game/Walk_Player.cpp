#include "framework.h"
#include "Walk_Player.h"

#include "Idle_Player.h"
#include "Jump_Player.h"

#include "InputManager.h"
#include "Player.h"

void Walk_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Walk");
}

void Walk_Player::Update(Player* player, float deltaTime)
{
    bool moved = false;

    // Walk 
    if (InputManager::Get().IsKeyDown(VK_LEFT)) {
        player->position.x -= player->speed * deltaTime;
        player->SetFlipX(true);  
        moved = true;
    }
    if (InputManager::Get().IsKeyDown(VK_RIGHT)) {
        player->position.x += player->speed * deltaTime;
        player->SetFlipX(false);
        moved = true;
    }

    // Jump 
    if (InputManager::Get().IsKeyDown(VK_UP)) {
        player->ChangeState(new Jump_Player());
        return;
    }

    // 입력 없으면 Idle
    if (!moved) {
        player->ChangeState(new Idle_Player());
    }
}

void Walk_Player::Exit(Player* player) {}