#pragma once

class Player;

class ActionState 
{
public:
    virtual ~ActionState() = default;
    virtual void Enter(Player* player) = 0;
    virtual void Update(Player* player, float deltaTime) = 0;
    virtual void Exit(Player* player) = 0;
};
