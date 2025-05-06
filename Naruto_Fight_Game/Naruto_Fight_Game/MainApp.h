#pragma once
#include "../GDIEngine_StaticLib/WindowGame.h"

class MainApp : public WindowGame
{
public:
	MainApp() = default;
	~MainApp() = default;

	virtual void Initialize() override;
	virtual void ShutDown() override;

	virtual void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	enum SceneType
	{
		Scene_Start,
		Scene_Map1,
		Scene_End
	};
};