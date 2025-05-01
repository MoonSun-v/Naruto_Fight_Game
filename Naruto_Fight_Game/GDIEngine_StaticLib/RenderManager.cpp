#include "pch.h"
#include "RenderManager.h"
#include "WindowGame.h"

void RenderManager::StartUp(HWND hwnd, int width, int height)
{
	// GdiplusStartup() : GDI+를 사용하기 위한 필수 호출
	Gdiplus::GdiplusStartupInput gsi;
	Gdiplus::GdiplusStartup(&g_GdiPlusToken, &gsi, nullptr);

	g_FrontBufferDC = GetDC(hwnd);							// 프론트 버퍼 DC를 윈도우 핸들로부터 가져옴
	g_BackBufferDC = CreateCompatibleDC(g_FrontBufferDC);	// 프론트 버퍼 DC와 호환되는 백 버퍼 DC 생성
	g_BackBufferBitmap = CreateCompatibleBitmap(g_FrontBufferDC, width, height);	// 프론트 버퍼와 같은 크기의 비트맵 생성
	SelectObject(g_BackBufferDC, g_BackBufferBitmap);		// 백 버퍼 DC에 비트맵 선택
	g_pBackBufferGraphics = new Gdiplus::Graphics(g_BackBufferDC);					// GDI+ Graphics 객체 생성
}

void RenderManager::ShutDown(HWND hwnd)
{
	delete g_pBackBufferGraphics;		// GDI+ Graphics 객체 삭제

	DeleteObject(g_BackBufferBitmap);	// 비트맵 삭제
	DeleteDC(g_BackBufferDC);			// 백 버퍼 DC 삭제
	ReleaseDC(hwnd, g_FrontBufferDC);   // 프론트 버퍼 DC 해제	
}

void RenderManager::DrawImage(Gdiplus::Bitmap* g_pCurrentFrame_, float posX_, float posY_)
{
	g_pBackBufferGraphics->DrawImage(g_pCurrentFrame_, posX_, posY_);
}

void RenderManager::DrawImageCenter(Gdiplus::Bitmap* bitmap, float centerX, float centerY)
{
	float x = centerX - bitmap->GetWidth() / 2.0f; 
	float y = centerY - bitmap->GetHeight() / 2.0f; 
	g_pBackBufferGraphics->DrawImage(bitmap, x, y);
}

void RenderManager::DrawAABB(const AABB& box, Gdiplus::Color color)
{
	if (!g_pBackBufferGraphics) return;

	Gdiplus::Pen pen(color, 2); // 선,곡선 그리기 

	float left = box.m_Center.x - box.m_Extent.x;
	float top = box.m_Center.y - box.m_Extent.y;
	float width = box.m_Extent.x * 2;
	float height = box.m_Extent.y * 2;

	g_pBackBufferGraphics->DrawRectangle(&pen, left, top, width, height);
}

void RenderManager::DrawText_w(const std::wstring& text, float x, float y, float fontSize, Gdiplus::Color color)
{
	if (g_BackBufferDC == nullptr) return;

	// 텍스트 출력에 사용할 GDI 폰트 생성
	LOGFONT logFont;
	ZeroMemory(&logFont, sizeof(LOGFONT));
	logFont.lfHeight = static_cast<int>(fontSize); // 폰트 크기 설정
	wcscpy_s(logFont.lfFaceName, L"Segoe UI");     // 사용할 폰트 설정

	// GDI 폰트 생성
	HFONT hFont = CreateFontIndirect(&logFont);
	SelectObject(g_BackBufferDC, hFont); // DC에 폰트 선택

	// 텍스트 출력
	SetTextColor(g_BackBufferDC, RGB(color.GetRed(), color.GetGreen(), color.GetBlue())); // 텍스트 색상 설정
	SetBkMode(g_BackBufferDC, TRANSPARENT); // 배경색 투명

	// 텍스트 출력
	TextOut(g_BackBufferDC, static_cast<int>(x), static_cast<int>(y), text.c_str(), static_cast<int>(text.length()));

	// 폰트 리소스 해제
	DeleteObject(hFont);
}