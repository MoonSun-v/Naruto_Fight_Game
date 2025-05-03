#pragma once
#include "PlayerActionState.h"

class Idle_Action_Player : public PlayerActionState
{
public:
    void Enter(Player* player) override { player->PlayAnimation(L"Idle", false); }
    void Update(Player* player, float deltaTime) override {}
    void Exit(Player* player) override {}
};