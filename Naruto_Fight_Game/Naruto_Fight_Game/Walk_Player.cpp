#include "framework.h"
#include "Walk_Player.h"

#include "Idle_Player.h"
#include "Jump_Player.h"
#include "Run_Player.h"

#include "InputManager.h"
#include "TimeManager.h"
#include "Player.h"

void Walk_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Walk");
}

void Walk_Player::Update(Player* player, float deltaTime)
{
    const auto& keys = player->GetKeySet();  // <- keySet�� �����ϰ� ��������
    
    bool moved = false;
    float currentTime = TimeManager::Get().GetTotalTime(); // ���� �ð�

    // Walk 
    // ���� �̵�
    if (InputManager::Get().IsKeyDown(keys.keyLeft)) {
        player->position.x -= player->speed * deltaTime;
        player->SetFlipX(true);
        moved = true;
    }

    // ������ �̵�
    if (InputManager::Get().IsKeyDown(keys.keyRight)) {
        player->position.x += player->speed * deltaTime;
        player->SetFlipX(false);
        moved = true;
    }

    // Jump 
    if (InputManager::Get().IsKeyDown(keys.keyUp)) {
        player->ChangeMoveState(new Jump_Player(player->speed));
        return;
    }

    // �Է� ������ Idle
    if (!moved) {
        player->ChangeMoveState(new Idle_Player());
    }
}

void Walk_Player::Exit(Player* player) {}