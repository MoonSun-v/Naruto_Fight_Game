#pragma once

#include "PlayerActionState.h"
#include "PlayerState.h"
#include "Idle_Player.h"

class Idle_Action_Player : public PlayerActionState
{
public:
    void Enter(Player* player) override;
    void Update(Player* player, float deltaTime) override;
    void Exit(Player* player) override;
};