#include "framework.h"
#include "Attack_Player.h"

#include "Idle_Player.h"
#include "Jump_Player.h"

#include "InputManager.h"
#include "Player.h"

void Attack_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Attack");
    attackTime = 0.0f;
}

void Attack_Player::Update(Player* player, float deltaTime)
{
    attackTime += deltaTime;

    // 이동 입력 처리
    
    if (InputManager::Get().IsKeyDown(VK_LEFT)) {
        player->position.x -= player->speed * deltaTime;
        player->SetFlipX(true);
    }
    if (InputManager::Get().IsKeyDown(VK_RIGHT)) {
        player->position.x += player->speed * deltaTime;
        player->SetFlipX(false);
    }
    
    if (attackTime >= attackDuration)
    {
        player->ChangeState(new Idle_Player());
    }
}

void Attack_Player::Exit(Player* player) {}