#include "framework.h"
#include "Attack_Action_Player.h"
#include "Player.h"
#include "Idle_Action_Player.h"
#include "AttackCombo_Action_Player.h"
#include "InputManager.h"

void Attack_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Attack", false);
    elapsedTime = 0.0f;
    comboInputTime = false;
}

void Attack_Action_Player::Update(Player* player, float deltaTime)
{
    elapsedTime += deltaTime;

    // D Ű �Է��� ������ �޺� ����
    if (InputManager::Get().IsKeyPressed('D') && elapsedTime > 0.3f) {
        comboQueued = true;
    }

    // �ִϸ��̼� �������� Ȯ��
    /*
    if (player->GetAnimator().IsAnimationFinished()) 
    {
        if (comboQueued)    player->ChangeActionState(new AttackCombo_Action_Player());
        else                player->ChangeActionState(new Idle_Action_Player());
    }
    */
    if (player->GetAnimator().IsAnimationFinished())
    {
        player->ChangeActionState(new Idle_Action_Player());
    }
}

void Attack_Action_Player::Exit(Player* player) {
    // �ƹ� �۾� ����
}