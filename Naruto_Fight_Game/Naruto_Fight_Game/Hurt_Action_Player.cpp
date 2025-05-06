#include "framework.h"
#include "Player.h"
#include "Hurt_Action_Player.h"
#include "Idle_Action_Player.h"

void Hurt_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Hurt_Short", false);
    player->TakeDamage(2.0f);

    float hp = player->GetHP();

    wchar_t buffer[100];
    swprintf_s(buffer, 100, L"[HP] ���� ü��: %.1f\n", hp);
    OutputDebugString(buffer);

    if (player->IsDead())
    {
        // player->ChangeActionState(new Die_Action_Player());
        OutputDebugString(L"[GameOver] �÷��̾ ����߽��ϴ�!\n");
    }
}

void Hurt_Action_Player::Update(Player* player, float deltaTime)
{
    if (player->GetAnimator().IsAnimationFinished())    player->ChangeActionState(new Idle_Action_Player());
}

void Hurt_Action_Player::Exit(Player* player) {
    // �ƹ� �۾� ����
}