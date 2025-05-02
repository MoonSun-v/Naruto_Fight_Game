#pragma once
#include "PlayerState.h"

class Attack_Player : public PlayerState
{
public:
    void Enter(Player* player) override;
    void Update(Player* player, float deltaTime) override;
    void Exit(Player* player) override;

private:
    float attackTime = 0.0f;
    const float attackDuration = 0.4f; // ���� �ִϸ��̼� �ð� (0.4�� ��)
};