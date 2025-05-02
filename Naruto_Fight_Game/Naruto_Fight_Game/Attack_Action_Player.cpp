#include "framework.h"
#include "Attack_Action_Player.h"
#include "Player.h"
#include "Idle_Action_Player.h"

void Attack_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Attack", true);
    elapsedTime = 0.0f;
}

void Attack_Action_Player::Update(Player* player, float deltaTime)
{
    elapsedTime += deltaTime;
    if (elapsedTime >= attackDuration)
    {
        player->ChangeActionState(new Idle_Action_Player());
    }
}

void Attack_Action_Player::Exit(Player* player) {
    // 아무 작업 없음
}
