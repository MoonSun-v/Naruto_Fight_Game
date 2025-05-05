#include "framework.h"
#include "Idle_Action_Player.h"
#include "Player.h"

void Idle_Action_Player::Enter(Player* player)
{
    player->ChangeMoveState(new Idle_Player());
}

void Idle_Action_Player::Update(Player* player, float deltaTime)
{
    
}

void Idle_Action_Player::Exit(Player* player) {
    // 아무 작업 없음
}
