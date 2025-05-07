#include "framework.h"
#include "Player.h"
#include "Die_Action_Player.h"

void Die_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Die", false);
}

void Die_Action_Player::Update(Player* player, float deltaTime)
{

}

void Die_Action_Player::Exit(Player* player)
{

}

