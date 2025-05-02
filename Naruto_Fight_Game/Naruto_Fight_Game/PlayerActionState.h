#pragma once
class Player;

class PlayerActionState
{
public:
    virtual ~PlayerActionState() = default;
    virtual void Enter(Player* player) = 0;
    virtual void Update(Player* player, float deltaTime) = 0;
    virtual void Exit(Player* player) = 0;
};