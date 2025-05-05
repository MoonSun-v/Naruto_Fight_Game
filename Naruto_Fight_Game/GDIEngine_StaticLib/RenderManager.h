#pragma once
#include "Singleton.h"
#include "../Vector2_StaticLib/AABB.h"

// [ 더블버퍼링, 이미지 출력 기능 제공 ]

class RenderManager : public Singleton<RenderManager>
{
private:
	HDC g_FrontBufferDC;        // 프론트 버퍼 DC (화면 출력용)
	HDC g_BackBufferDC;         // 백 버퍼 DC (메모리 상의 버퍼)
	HBITMAP g_BackBufferBitmap; // 백버퍼 비트맵

	ULONG_PTR g_GdiPlusToken; // GDI+ 초기화 및 종료 관리하는 핸들            

	Gdiplus::Graphics* g_pBackBufferGraphics = nullptr; // 백버퍼에 그릴 GDI+ Graphics 객체

public:
	RenderManager() = default;
	~RenderManager() = default;

	void StartUp(HWND hwnd, int width, int height);

	void ShutDown(HWND hwnd);

	void DrawImage(Gdiplus::Bitmap* g_pCurrentFrame_, float posX_, float posY_);
	void DrawImage(Gdiplus::Bitmap* g_pCurrentFrame_, float posX_, float posY_, float width_, float height_);
	void DrawImageCenter(Gdiplus::Bitmap* bitmap, float centerX, float centerY);

	// Atlas Bitmap Image
	void DrawImageClip(Gdiplus::Bitmap* bitmap, float x, float y, const Gdiplus::Rect& srcRect, bool flipX = false);
	void DrawImageClipWithColorKey(Gdiplus::Bitmap* bitmap, float x, float y, const Gdiplus::Rect& srcRect, Gdiplus::Color transparentColor, bool flipX = false);

	// [ 더블 버퍼링을 활용한 Draw 함수들 ] 백 버퍼에 그린 후 -> 프론트 버퍼에 복사 
	// BeginDraw() -> Draw() -> EndDraw() 
	void BeginDraw()
	{
		PatBlt(g_BackBufferDC, 0, 0, 1024, 768, BLACKNESS); // 백 버퍼 초기화 
	}
	void EndDraw(int width, int height)
	{
		BitBlt(g_FrontBufferDC, 0, 0, width, height, g_BackBufferDC, 0, 0, SRCCOPY); // 백 버퍼의 내용을 프론트 버퍼로 복사 (더블 버퍼링)
	}
	 
	// [ AABB 경계 그리기 ]
	void DrawAABB(const AABB& box, Gdiplus::Color color = Gdiplus::Color::Red);

	// [ 텍스트 출력 ]
	void DrawText_w(const std::wstring& text, float x, float y, float fontSize, Gdiplus::Color color);
};