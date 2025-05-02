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
    float moveSpeed = 0.0f;      // ���� �̵� �ӵ� (�ȱ� or �޸��� ���¿� ���� ����)

    int lastKeyPressed = 0;       // ������ ����Ű (VK_LEFT �Ǵ� VK_RIGHT)
    float lastKeyTime = 0.0f;     // ������ ����Ű �Է� �ð�
    const float doubleTapThreshold = 0.8f; // 0.3�� �̳� �� �� ������ �� Run ��ȯ
    void ResetRunInput();

    // [ FSM ]
    void ChangeState(PlayerState* newState);
    void PlayAnimation(const std::wstring& name, bool force = false);

private:
    PlayerState* currentState = nullptr;

    // �������� �����ϱ� ���� ����
    float lastLeftPressTime = 0.0f;
    float lastRightPressTime = 0.0f;
};