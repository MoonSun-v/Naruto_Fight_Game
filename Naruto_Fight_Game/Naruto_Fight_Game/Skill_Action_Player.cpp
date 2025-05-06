#include "framework.h"
#include "Player.h"
#include "Skill_Action_Player.h"
#include "Idle_Action_Player.h"

void Skill_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Skill", false);
}

void Skill_Action_Player::Update(Player* player, float deltaTime)
{
    if (player->GetAnimator().IsAnimationFinished())
    {
        player->ChangeActionState(new Idle_Action_Player());
    }
}

void Skill_Action_Player::Exit(Player* player) {
    
}
