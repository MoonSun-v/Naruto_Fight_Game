#include "framework.h"
#include "Run_Player.h"

#include "Jump_Player.h"
#include "Walk_Player.h"

#include "InputManager.h"
#include "Player.h"

void Run_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Run");
}

void Run_Player::Update(Player* player, float deltaTime)
{
    const auto& keys = player->GetKeySet();

    float runSpeed = player->speed * 2.0f;
    bool moved = false;

    // �̵� �Է� ó��
    if (InputManager::Get().IsKeyDown(keys.keyLeft)) {
        player->position.x -= runSpeed * deltaTime;
        player->SetFlipX(true);
        moved = true;
    }
    else if (InputManager::Get().IsKeyDown(keys.keyRight)) {
        player->position.x += runSpeed * deltaTime;
        player->SetFlipX(false);
        moved = true;
    }

    // ���� �Է�
    if (InputManager::Get().IsKeyDown(keys.keyUp)) {
        player->ChangeMoveState(new Jump_Player(runSpeed));  // Run �ӵ� ����
        return;
    }

    if (!moved) {
        player->ChangeMoveState(new Walk_Player());  // ����Ű�� ���� �ȱ�� ��ȯ
    }
}

void Run_Player::Exit(Player* player)
{
    // Ư���� ���� �۾��� ����
}