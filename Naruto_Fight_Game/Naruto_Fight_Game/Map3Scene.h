#pragma once
#include "../GDIEngine_StaticLib/Scene.h"

class Map3Scene : public Scene
{
public:
	Map3Scene() = default;
	~Map3Scene() = default;

	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;
};
