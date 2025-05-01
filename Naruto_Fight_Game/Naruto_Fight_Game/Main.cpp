// Main.cpp : 애플리케이션에 대한 진입점 정의.

#include "framework.h"
#include "Main.h"
#include "MainApp.h"

// [ Windows 앱의 메인 함수 ] wWinMain : 유니코드 사용 버전 (wchar_t)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    MainApp app;

    app.Initialize();

    app.Run();          // PeekMessage 루프 돌면서 Update(), Render()가 반복 실행

    app.ShutDown();     // 종료 전 자원 정리 

    return (int)1;
}