#pragma once

class Enemy1;

class Enemy1State
{
public:
    virtual ~Enemy1State() = default;

    virtual void Enter(Enemy1* player) = 0;
    virtual void Update(Enemy1* player, float deltaTime) = 0;
    virtual void Exit(Enemy1* player) = 0;
};