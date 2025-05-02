#pragma once

#include "Character.h"
#include "PlayerState.h"

class Player : public Character
{
public:
    Player();
    ~Player();

    void Update() override;
    void Render() override;

    float speed = 200;

    // FSM
    void ChangeState(PlayerState* newState);
    void PlayAnimation(const std::wstring& name, bool force = false);

private:
    PlayerState* currentState = nullptr;
};