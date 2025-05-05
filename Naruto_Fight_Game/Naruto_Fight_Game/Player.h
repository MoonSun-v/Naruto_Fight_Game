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
        int keyUp;      // �ʿ��ϴٸ�
        int keyAttack;
        int keyThrow;
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

    void TakeDamage();
    bool IsAttacking() const;
    bool IsHurt() const;

    bool m_HasHitThisAttack = false;    // ���� ���� �� �ǰ� ����
    bool m_HasCollidedWithTarget = false; // ���� �浹 �� ����
    bool m_AttackStartedThisFrame = false;

private:

    PlayerState* moveState = nullptr;
    PlayerActionState* actionState = nullptr;

    // �������� �����ϱ� ���� ����
    float lastLeftPressTime = 0.0f;
    float lastRightPressTime = 0.0f;

    void PlayAttack();
    void PlayMove(float currentTime);
};