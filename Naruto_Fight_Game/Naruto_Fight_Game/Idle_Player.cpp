#include "framework.h"
#include "Idle_Player.h"

#include "Walk_Player.h"
#include "Jump_Player.h"

#include "InputManager.h"
#include "Player.h"

void Idle_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Idle");
}

void Idle_Player::Update(Player* player, float deltaTime)
{
    const auto& keys = player->GetKeySet();  

    if (InputManager::Get().IsKeyDown(keys.keyLeft) || InputManager::Get().IsKeyDown(keys.keyRight))
    {
        player->ChangeMoveState(new Walk_Player());
    }
    if (InputManager::Get().IsKeyPressed(keys.keyUp))
    {
        player->ChangeMoveState(new Jump_Player(player->moveSpeed));
    }
}

void Idle_Player::Exit(Player* player) {}