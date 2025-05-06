#pragma once
#include "../GDIEngine_StaticLib/Scene.h"

class StartScene : public Scene
{
public:
	StartScene() = default;
	~StartScene() = default;

	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;

	Gdiplus::Bitmap* StartTitle = nullptr;
};
