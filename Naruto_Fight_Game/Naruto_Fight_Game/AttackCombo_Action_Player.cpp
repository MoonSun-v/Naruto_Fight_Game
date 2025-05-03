#include "framework.h"
#include "Player.h"
#include "AttackCombo_Action_Player.h"
#include "Idle_Action_Player.h"

void AttackCombo_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"ComboAttack", false);
}

void AttackCombo_Action_Player::Update(Player* player, float deltaTime)
{
    if (player->GetAnimator().IsAnimationFinished()) {
        player->ChangeActionState(new Idle_Action_Player());
    }
}

void AttackCombo_Action_Player::Exit(Player* player) {
    // 아무 작업 없음
}