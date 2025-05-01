// Main.cpp : ���ø����̼ǿ� ���� ������ ����.

#include "framework.h"
#include "Main.h"
#include "MainApp.h"

// [ Windows ���� ���� �Լ� ] wWinMain : �����ڵ� ��� ���� (wchar_t)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    MainApp app;

    app.Initialize();

    app.Run();          // PeekMessage ���� ���鼭 Update(), Render()�� �ݺ� ����

    app.ShutDown();     // ���� �� �ڿ� ���� 

    return (int)1;
}