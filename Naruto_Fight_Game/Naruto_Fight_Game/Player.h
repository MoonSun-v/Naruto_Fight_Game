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
    float moveSpeed = 0.0f;      // ���� �̵� �ӵ� (�ȱ� or �޸��� ���¿� ���� ����)

    int lastKeyPressed = 0;       // ������ ����Ű (VK_LEFT �Ǵ� VK_RIGHT)
    float lastKeyTime = 0.0f;     // ������ ����Ű �Է� �ð�
    const float doubleTapThreshold = 0.8f; // 0.8�� �̳� �� �� ������ �� Run ��ȯ
    void ResetRunInput();

    // [ FSM ]
    void ChangeMoveState(PlayerState* newState);
    void ChangeActionState(PlayerActionState* newState);

    // [ �ִϸ��̼� ]
    void PlayAnimation(const std::wstring& name, bool force = false);
    Animator& GetAnimator() { return animator; }

    
    bool IsAttacking() const;
    bool IsSkill() const;
    bool IsHurt() const;

    bool m_HasHitThisAttack = false;    // ���� ���� �� �ǰ� ����
    bool m_HasCollidedWithTarget = false; // ���� �浹 �� ����
    bool m_AttackStartedThisFrame = false;
    int m_HitComboCount = 0;

private:

    PlayerState* moveState = nullptr;
    PlayerActionState* actionState = nullptr;

    // �������� �����ϱ� ���� ����
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

    // �ʱ�ȭ
    void SetStats(float _maxHp, float _maxMp)
    {
        maxHp = _maxHp;
        hp = _maxHp;
        maxMp = _maxMp;
        mp = 0;
    }

    // ------ MP ���� --------
    void UpdateMP();
    bool CanThrowWeapon() const;
    bool CanUseSkill() const;
    void ConsumeMP(float amount);

    bool isInputLocked = false;

    // void SetAnimationResource(const std::wstring& imagePath, const std::wstring& animPath);
};