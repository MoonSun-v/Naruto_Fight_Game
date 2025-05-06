#pragma once
#include "PlayerActionState.h"

class Skill_Action_Player : public PlayerActionState
{
public:
    void Enter(Player* player) override;
    void Update(Player* player, float deltaTime) override;
    void Exit(Player* player) override;

private:
    float elapsed = 0.0f;

    const float moveSpeed = 300.0f;
    const float totalDistance = 600.0f;
    float movedDistance = 0.0f;

    bool damageApplied = false;

    void SetInputLockForAllPlayers(bool lock);
};