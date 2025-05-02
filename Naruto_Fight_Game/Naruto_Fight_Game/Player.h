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

    // FSM
    void ChangeState(PlayerState* newState);
    void PlayAnimation(const std::wstring& name, bool force = false);
    // void SetFlipX(bool flip);

private:
    PlayerState* currentState = nullptr;
};