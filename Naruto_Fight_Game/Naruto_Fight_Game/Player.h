#pragma once

#include "Character.h"
#include "PlayerState.h"
#include "PlayerActionState.h"

class Player : public Character
{
public:
    struct KeySet
    {
        int keyLeft;
        int keyRight;
        int keyUp;      // 필요하다면
        int keyAttack;
        int keyThrow;
    };

    KeySet keySet;
    void SetKeySet(const KeySet& keys);
    const KeySet& GetKeySet() const { return keySet; }

    Player();
    ~Player();

    void Update() override;
    void Render() override;

    float speed = 200;
    float moveSpeed = 0.0f;      // 현재 이동 속도 (걷기 or 달리기 상태에 따라 변경)

    int lastKeyPressed = 0;       // 마지막 방향키 (VK_LEFT 또는 VK_RIGHT)
    float lastKeyTime = 0.0f;     // 마지막 방향키 입력 시간
    const float doubleTapThreshold = 0.8f; // 0.8초 이내 두 번 눌렀을 때 Run 전환
    void ResetRunInput();

    // [ FSM ]
    void ChangeMoveState(PlayerState* newState);
    void ChangeActionState(PlayerActionState* newState);

    // [ 애니메이션 ]
    void PlayAnimation(const std::wstring& name, bool force = false);
    Animator& GetAnimator() { return animator; }

    void TakeDamage();

private:

    PlayerState* moveState = nullptr;
    PlayerActionState* actionState = nullptr;

    // 더블탭을 감지하기 위한 변수
    float lastLeftPressTime = 0.0f;
    float lastRightPressTime = 0.0f;

    void PlayAttack();
    void PlayMove(float currentTime);
};