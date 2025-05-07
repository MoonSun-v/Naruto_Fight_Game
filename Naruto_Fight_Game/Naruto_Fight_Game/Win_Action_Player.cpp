#include "framework.h"
#include "Player.h"
#include "Win_Action_Player.h"

void Win_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Win", false);
}

void Win_Action_Player::Update(Player* player, float deltaTime)
{

}

void Win_Action_Player::Exit(Player* player)
{
    
}

