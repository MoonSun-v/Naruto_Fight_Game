#pragma once
#include "PlayerActionState.h"

class Hurt_Action_Player : public PlayerActionState
{
public:
    void Enter(Player* player) override;
    void Update(Player* player, float deltaTime) override;
    void Exit(Player* player) override;
};