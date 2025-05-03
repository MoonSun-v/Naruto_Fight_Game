#include "framework.h"
#include "Idle_Player.h"
#include "Throw_Action_Player.h"
#include "Player.h"

void Throw_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Throw_Action", false);
}

void Throw_Action_Player::Update(Player* player, float deltaTime)
{
    if (player->GetAnimator().IsAnimationFinished()) player->ChangeMoveState(new Idle_Player());
}

void Throw_Action_Player::Exit(Player* player) {
    
}