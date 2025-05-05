#pragma once
#include "Singleton.h"
#include "../Vector2_StaticLib/AABB.h"

// [ ������۸�, �̹��� ��� ��� ���� ]

class RenderManager : public Singleton<RenderManager>
{
private:
	HDC g_FrontBufferDC;        // ����Ʈ ���� DC (ȭ�� ��¿�)
	HDC g_BackBufferDC;         // �� ���� DC (�޸� ���� ����)
	HBITMAP g_BackBufferBitmap; // ����� ��Ʈ��

	ULONG_PTR g_GdiPlusToken; // GDI+ �ʱ�ȭ �� ���� �����ϴ� �ڵ�            

	Gdiplus::Graphics* g_pBackBufferGraphics = nullptr; // ����ۿ� �׸� GDI+ Graphics ��ü

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

	// [ ���� ���۸��� Ȱ���� Draw �Լ��� ] �� ���ۿ� �׸� �� -> ����Ʈ ���ۿ� ���� 
	// BeginDraw() -> Draw() -> EndDraw() 
	void BeginDraw()
	{
		PatBlt(g_BackBufferDC, 0, 0, 1024, 768, BLACKNESS); // �� ���� �ʱ�ȭ 
	}
	void EndDraw(int width, int height)
	{
		BitBlt(g_FrontBufferDC, 0, 0, width, height, g_BackBufferDC, 0, 0, SRCCOPY); // �� ������ ������ ����Ʈ ���۷� ���� (���� ���۸�)
	}
	 
	// [ AABB ��� �׸��� ]
	void DrawAABB(const AABB& box, Gdiplus::Color color = Gdiplus::Color::Red);

	// [ �ؽ�Ʈ ��� ]
	void DrawText_w(const std::wstring& text, float x, float y, float fontSize, Gdiplus::Color color);
};