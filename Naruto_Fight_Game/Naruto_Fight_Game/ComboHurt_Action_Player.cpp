#include "framework.h"
#include "ComboHurt_Action_Player.h"
#include "Idle_Action_Player.h"
#include "Player.h"
#include "Die_Action_Player.h"

void ComboHurt_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Hurt_Long", false);
}

void ComboHurt_Action_Player::Update(Player* player, float deltaTime)
{
    if (player->GetAnimator().IsAnimationFinished())    player->ChangeActionState(new Idle_Action_Player());
}

void ComboHurt_Action_Player::Exit(Player* player) 
{
    player->TakeDamage(0.2f);
    player->IncreaseMP(0.1f);
}
