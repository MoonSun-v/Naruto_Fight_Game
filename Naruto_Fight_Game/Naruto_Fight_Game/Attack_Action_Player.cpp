#include "framework.h"
#include "Attack_Action_Player.h"
#include "Player.h"
#include "Idle_Action_Player.h"
#include "AttackCombo_Action_Player.h"
#include "InputManager.h"

void Attack_Action_Player::Enter(Player* player)
{
    player->m_HasHitThisAttack = false;
    player->m_HasCollidedWithTarget = false;
    player->m_AttackStartedThisFrame = true;  // �߰�
    player->PlayAnimation(L"Attack", false);
    elapsedTime = 0.0f;
    comboInputTime = 0.0f;
    comboQueued = false;
}

void Attack_Action_Player::Update(Player* player, float deltaTime)
{
    const auto& keys = player->GetKeySet();

    elapsedTime += deltaTime;
    comboInputTime += deltaTime;

    // Ű �� ������ �Ǵ�
    if (InputManager::Get().IsKeyDown(keys.keyAttack)) comboInputTime += deltaTime;
    else                                    comboInputTime = 0.0f; // �� ������ �ʱ�ȭ

    if (comboInputTime >= 0.6f) comboQueued = true; // �޺� ���� ����

    if (player->GetAnimator().IsAnimationFinished())
    {
        if (comboQueued)    player->ChangeActionState(new AttackCombo_Action_Player());
        else                player->ChangeActionState(new Idle_Action_Player());
    }
}

void Attack_Action_Player::Exit(Player* player) {
    // �ƹ� �۾� ����
}