#include "framework.h"
#include "Enemy1.h"

#include "Walk_Enemy1.h"

#include "TimeManager.h"

#include <fstream>
#include <sstream>

Enemy1::Enemy1()
	: Character(L"../Resources/Sasuke.png", L"../Resources/Animation/Sasuke.txt")
{
	// transparentColor = Gdiplus::Color(0, 128, 0); // 이미지 배경 투명 처리
	ChangeState(new Walk_Enemy1());
}

Enemy1::~Enemy1() = default;

void Enemy1::Update()
{
	__super::Update();

	float deltaTime = TimeManager::Get().GetDeltaTime();

	enemy1State->Update(this, deltaTime);
}

void Enemy1::Render()
{
	__super::Render();

}

void Enemy1::PlayAnimation(const std::wstring& name, bool force)
{
	animator.Play(name, force);
}

void Enemy1::ChangeState(Enemy1State* newState)
{
	if (enemy1State) enemy1State->Exit(this);
	delete enemy1State;
	enemy1State = newState;
	if (enemy1State) enemy1State->Enter(this);
}