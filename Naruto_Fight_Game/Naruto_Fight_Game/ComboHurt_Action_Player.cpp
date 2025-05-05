#include "framework.h"
#include "ComboHurt_Action_Player.h"
#include "Idle_Action_Player.h"
#include "Player.h"

void ComboHurt_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Hurt_Long", false);
    // player->TakeDamage();
    OutputDebugString(L"ComboHurt !\n");
}

void ComboHurt_Action_Player::Update(Player* player, float deltaTime)
{
    if (player->GetAnimator().IsAnimationFinished())    player->ChangeActionState(new Idle_Action_Player());
}

void ComboHurt_Action_Player::Exit(Player* player) {
    // 아무 작업 없음
}
