#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player();
	~Player() override;
	void Update() override;
};