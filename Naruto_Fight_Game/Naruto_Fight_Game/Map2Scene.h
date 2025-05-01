#pragma once
#include "../GDIEngine_StaticLib/Scene.h"

class Map2Scene : public Scene
{
public:
	Map2Scene() = default;
	~Map2Scene() = default;

	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;
};

