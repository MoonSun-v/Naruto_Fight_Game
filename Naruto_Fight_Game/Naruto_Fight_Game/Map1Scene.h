#pragma once
#include "../GDIEngine_StaticLib/Scene.h"
#include "Player.h"

class Map1Scene : public Scene
{
public:
	Map1Scene() = default;
	~Map1Scene() = default;

	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;

	Player* player1 = nullptr;
	Player* player2 = nullptr;

	bool m_GameOver = false; 
	float m_EndSceneTimer = 0.0f;
	bool m_WaitingForSceneChange = false;


	// 스킬 관련 이미지 
	enum class SkillOwner { None, Player1, Player2 };
	SkillOwner m_SkillEffectOwner = SkillOwner::None;

	Gdiplus::Bitmap* m_SkillEffectImage = nullptr;
	float m_SkillEffectTimer = 0.0f;
	const float m_SkillEffectDuration = 5.0f;

	Gdiplus::Bitmap* m_WinnerImage = nullptr;
};
