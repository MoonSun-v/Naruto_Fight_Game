#pragma once
#include "PlayerActionState.h"

class Skill_Action_Player : public PlayerActionState
{
public:
    void Enter(Player* player) override;
    void Update(Player* player, float deltaTime) override;
    void Exit(Player* player) override;

    float elapsed = 0.0f;

    float m_MoveSpeed = 300.0f; 
    float m_TotalDistance = 600.0f;
    float m_MoveDistance = 0.0f;
    bool m_DamageApplied = false;
};