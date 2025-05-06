#include "framework.h"
#include "ComboHurt_Action_Player.h"
#include "Idle_Action_Player.h"
#include "Player.h"

void ComboHurt_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Hurt_Long", false);
    // player->TakeDamage(0.3f);
    // OutputDebugString(L"ComboHurt !\n");
}

void ComboHurt_Action_Player::Update(Player* player, float deltaTime)
{
    if (player->GetAnimator().IsAnimationFinished())    player->ChangeActionState(new Idle_Action_Player());
}

void ComboHurt_Action_Player::Exit(Player* player) {
    player->TakeDamage(0.2f);
    player->IncreaseMP(0.1f);
    if (player->IsDead())
    {
        // player->ChangeActionState(new Die_Action_Player());
        OutputDebugString(L"[GameOver] 플레이어가 사망했습니다!\n");
    }
}
