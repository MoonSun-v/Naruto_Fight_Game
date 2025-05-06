#include "framework.h"
#include "Player.h"
#include "Die_Action_Player.h"

void Die_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Die", false);
}

void Die_Action_Player::Update(Player* player, float deltaTime)
{
    // if (player->GetAnimator().IsAnimationFinished())    player->ChangeActionState(new Idle_Action_Player());
}

void Die_Action_Player::Exit(Player* player)
{
    // OutputDebugString(L"[GameOver] 플레이어가 사망했습니다!\n");
}

