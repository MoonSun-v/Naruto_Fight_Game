#pragma once
#include "PlayerState.h"

class Walk_Player : public PlayerState
{
public:
    void Enter(Player* player) override;
    void Update(Player* player, float deltaTime) override;
    void Exit(Player* player) override;
};