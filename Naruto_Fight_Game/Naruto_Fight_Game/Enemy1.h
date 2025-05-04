#pragma once
#include "Character.h"
#include "Enemy1State.h"

class Enemy1 : public Character
{
public:
	Enemy1();
	~Enemy1();

	void Update() override;
	void Render() override;

	// [ 애니메이션 ]
	void PlayAnimation(const std::wstring& name, bool force = false);
	Animator& GetAnimator() { return animator; }

	void ChangeState(Enemy1State* newState);

private:
	Enemy1State* enemy1State = nullptr;
};