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
        int keyUp;      
        int keyAttack;
        int keyThrow;
        int keySkill;
    };

    KeySet keySet;
    void SetKeySet(const KeySet& keys);
    const KeySet& GetKeySet() const { return keySet; }

    // Player();
    Player(const std::wstring& imagePath, const std::wstring& animPath);
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

    
    bool IsAttacking() const;
    bool IsSkill() const;
    bool IsHurt() const;

    bool m_HasHitThisAttack = false;    // 현재 공격 중 피격 여부
    bool m_HasCollidedWithTarget = false; // 현재 충돌 중 여부
    bool m_AttackStartedThisFrame = false;
    int m_HitComboCount = 0;

private:

    PlayerState* moveState = nullptr;
    PlayerActionState* actionState = nullptr;

    // 더블탭을 감지하기 위한 변수
    float lastLeftPressTime = 0.0f;
    float lastRightPressTime = 0.0f;

    void PlayAttack();
    void PlayMove(float currentTime);

protected:
    float hp;
    float maxHp;
    float mp;
    float maxMp;

    float MPRecoveryTimer = 0.0f;

public:
    float SetHP(float value);
    float SetMP(float value);

    float GetHP() const { return hp; }
    float GetMP() const { return mp; }

    void TakeDamage(float damage);
    void IncreaseMP(float value);
    bool IsDead() const { return hp <= 0; }

    // 초기화
    void SetStats(float _maxHp, float _maxMp)
    {
        maxHp = _maxHp;
        hp = _maxHp;
        maxMp = _maxMp;
        mp = 0;
    }

    // ------ MP 관련 --------
    void UpdateMP();
    bool CanThrowWeapon() const;
    bool CanUseSkill() const;
    void ConsumeMP(float amount);

    bool isInputLocked = false;

    // void SetAnimationResource(const std::wstring& imagePath, const std::wstring& animPath);
};