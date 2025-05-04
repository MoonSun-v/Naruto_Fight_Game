#pragma once
#include "Enemy1State.h"

class Walk_Enemy1 : public Enemy1State
{
public:
    void Enter(Enemy1* player) override;
    void Update(Enemy1* player, float deltaTime) override;
    void Exit(Enemy1* player) override;
};