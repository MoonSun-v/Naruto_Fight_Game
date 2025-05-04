#pragma once
#include "PlayerState.h"

class Jump_Player : public PlayerState
{
public:
    Jump_Player(float initialSpeed); // 달리기 속도 전달받는 생성자

    void Enter(Player* player) override;
    void Update(Player* player, float deltaTime) override;
    void Exit(Player* player) override;

private:
    float jumpTime = 0.0f;
    float duration = 0.5f;  // 점프 지속 시간
    float jumpHeight = 100.0f;
    float startY = 0.0f;

    float horizontalSpeed = 0.0f; // 점프 중 좌우 이동 속도
};