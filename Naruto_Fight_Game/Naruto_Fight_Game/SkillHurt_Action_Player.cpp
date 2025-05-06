#include "framework.h"
#include "Player.h"
#include "SkillHurt_Action_Player.h"
#include "Idle_Action_Player.h"
#include "Die_Action_Player.h"

void SkillHurt_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"SkillHurt", false);
}

void SkillHurt_Action_Player::Update(Player* player, float deltaTime)
{
    if (player->GetAnimator().IsAnimationFinished())    player->ChangeActionState(new Idle_Action_Player());
}

void SkillHurt_Action_Player::Exit(Player* player)
{
    player->TakeDamage(20.0f);
    player->IncreaseMP(5.0f);

    if (player->IsDead()) player->ChangeActionState(new Die_Action_Player());
}