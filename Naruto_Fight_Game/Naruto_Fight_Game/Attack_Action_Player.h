#pragma once
#include "PlayerActionState.h"

class Attack_Action_Player : public PlayerActionState
{
public:
    void Enter(Player* player) override;
    void Update(Player* player, float deltaTime) override;
    void Exit(Player* player) override;

private:
    float attackDuration = 0.3f;
    float elapsedTime = 0.0f;

    bool comboQueued = false;
    float comboInputTime = 0.4f; // 0.4초 이내에 누르면 콤보로 인정
};