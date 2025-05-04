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
    if (InputManager::Get().IsKeyDown(VK_LEFT) || InputManager::Get().IsKeyDown(VK_RIGHT))
    {
        player->ChangeMoveState(new Walk_Player());
    }
    if (InputManager::Get().IsKeyPressed(VK_UP))
    {
        player->ChangeMoveState(new Jump_Player(player->moveSpeed));
    }
}

void Idle_Player::Exit(Player* player) {}