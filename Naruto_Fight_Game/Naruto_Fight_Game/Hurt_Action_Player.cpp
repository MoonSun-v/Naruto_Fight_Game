#include "framework.h"
#include "Player.h"
#include "Hurt_Action_Player.h"
#include "Idle_Action_Player.h"

void Hurt_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Hurt_Short", false);
    player->TakeDamage();
}

void Hurt_Action_Player::Update(Player* player, float deltaTime)
{
    if (player->GetAnimator().IsAnimationFinished())    player->ChangeActionState(new Idle_Action_Player());
}

void Hurt_Action_Player::Exit(Player* player) {
    // 아무 작업 없음
}