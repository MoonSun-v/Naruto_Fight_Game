#pragma once
#include "../GDIEngine_StaticLib/Scene.h"

class EndScene : public Scene
{
public:
	EndScene() = default;
	~EndScene() = default;

	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;
};
#pragma once
