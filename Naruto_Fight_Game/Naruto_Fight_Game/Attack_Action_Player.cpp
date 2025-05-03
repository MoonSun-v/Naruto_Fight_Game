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
    comboInputTime = 0.0f;
    comboCount = 0;
    comboQueued = false;
}

void Attack_Action_Player::Update(Player* player, float deltaTime)
{
    elapsedTime += deltaTime;
    comboInputTime += deltaTime;

    // Ű �� ������ �Ǵ�
    if (InputManager::Get().IsKeyDown('D')) {
        comboInputTime += deltaTime;
    }
    else {
        comboInputTime = 0.0f; // �� ������ �ʱ�ȭ
    }

    if (comboInputTime >= 0.6f) {
        comboQueued = true; // �޺� ���� ����
    }

    if (player->GetAnimator().IsAnimationFinished())
    {
        if (comboQueued)    player->ChangeActionState(new AttackCombo_Action_Player());
        else                player->ChangeActionState(new Idle_Action_Player());
    }
}

void Attack_Action_Player::Exit(Player* player) {
    // �ƹ� �۾� ����
}