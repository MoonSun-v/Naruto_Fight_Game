#include "framework.h"
#include "Idle_Player.h"
#include "Walk_Player.h"
#include "Player.h"
#include "InputManager.h"

void Idle_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Idle");
}

void Idle_Player::Update(Player* player, float deltaTime)
{
    if (InputManager::Get().IsKeyDown(VK_LEFT) || InputManager::Get().IsKeyDown(VK_RIGHT))
    {
        player->ChangeState(new Walk_Player());
    }
}

void Idle_Player::Exit(Player* player) {}