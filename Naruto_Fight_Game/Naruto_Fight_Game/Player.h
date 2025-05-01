#pragma once

#include "Character.h"

class Player : public Character
{
public:
    Player();
    ~Player();

    void Update() override;
    void Render() override;
};