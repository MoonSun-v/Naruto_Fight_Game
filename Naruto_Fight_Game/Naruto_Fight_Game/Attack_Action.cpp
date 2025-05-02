#include "framework.h"
#include "Attack_Action.h"
#include "Player.h"
#include "Idle_Action.h"

void Attack_Action::Enter(Player* player) 
{
    player->PlayAnimation(L"Attack", true);
    elapsedTime = 0.0f;
}

void Attack_Action::Update(Player* player, float deltaTime) 
{
    elapsedTime += deltaTime;
    if (elapsedTime >= attackDuration) 
    {
        player->ChangeActionState(new Idle_Action());
    }
}

void Attack_Action::Exit(Player* player) {
    // 아무 작업 없음
}
