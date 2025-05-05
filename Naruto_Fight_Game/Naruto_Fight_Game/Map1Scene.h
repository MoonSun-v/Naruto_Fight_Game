#pragma once
#include "../GDIEngine_StaticLib/Scene.h"

class Map1Scene : public Scene
{
public:
	Map1Scene() = default;
	~Map1Scene() = default;

	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;
};
