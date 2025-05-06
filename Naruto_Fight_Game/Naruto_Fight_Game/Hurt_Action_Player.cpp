#include "framework.h"
#include "Player.h"
#include "Hurt_Action_Player.h"
#include "Idle_Action_Player.h"

void Hurt_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Hurt_Short", false);
}

void Hurt_Action_Player::Update(Player* player, float deltaTime)
{
    if (player->GetAnimator().IsAnimationFinished())    player->ChangeActionState(new Idle_Action_Player());
}

void Hurt_Action_Player::Exit(Player* player) 
{
    player->TakeDamage(2.0f);
    player->IncreaseMP(1.0f);
    if (player->IsDead())
    {
        // player->ChangeActionState(new Die_Action_Player());
        OutputDebugString(L"[GameOver] 플레이어가 사망했습니다!\n");
    }
}