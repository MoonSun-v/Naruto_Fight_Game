#include "framework.h"
#include "Walk_Player.h"
#include "Idle_Player.h"
#include "Player.h"
#include "InputManager.h"

void Walk_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Walk");
}

void Walk_Player::Update(Player* player, float deltaTime)
{
    float speed = 200.0f;
    bool moved = false;

    if (InputManager::Get().IsKeyDown(VK_LEFT)) {
        player->position.x -= speed * deltaTime;
        player->SetFlipX(true);  // �¿� ����
        moved = true;
    }
    if (InputManager::Get().IsKeyDown(VK_RIGHT)) {
        player->position.x += speed * deltaTime;
        player->SetFlipX(false);
        moved = true;
    }

    /*
    if (InputManager::Get().IsKeyDown(VK_UP)) {
        player->position.y -= speed * deltaTime;
        moved = true;
    }
    if (InputManager::Get().IsKeyDown(VK_DOWN)) {
        player->position.y += speed * deltaTime;
        moved = true;
    }
    */

    // ���� �Է� ����
    if (InputManager::Get().IsKeyDown(VK_UP)) {
        // player->ChangeState(new Jump_Player());
        return;
    }

    // �Է� ������ Idle��
    if (!moved) {
        player->ChangeState(new Idle_Player());
    }
}

void Walk_Player::Exit(Player* player) {}