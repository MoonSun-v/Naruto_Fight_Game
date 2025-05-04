#pragma once
#include "PlayerState.h"

class Jump_Player : public PlayerState
{
public:
    Jump_Player(float initialSpeed); // �޸��� �ӵ� ���޹޴� ������

    void Enter(Player* player) override;
    void Update(Player* player, float deltaTime) override;
    void Exit(Player* player) override;

private:
    float jumpTime = 0.0f;
    float duration = 0.5f;  // ���� ���� �ð�
    float jumpHeight = 100.0f;
    float startY = 0.0f;

    float horizontalSpeed = 0.0f; // ���� �� �¿� �̵� �ӵ�
};