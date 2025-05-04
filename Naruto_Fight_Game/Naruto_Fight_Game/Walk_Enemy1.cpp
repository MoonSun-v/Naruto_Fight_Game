#include "framework.h"
#include "Walk_Enemy1.h"

#include "Enemy1.h"

void Walk_Enemy1::Enter(Enemy1* enemy1)
{
	enemy1->PlayAnimation(L"Walk");
}

void Walk_Enemy1::Update(Enemy1* enemy1, float deltaTime)
{

}

void Walk_Enemy1::Exit(Enemy1* enemy1)
{

}