#include "pch.h"
#include "RenderManager.h"
#include "WindowGame.h"

void RenderManager::StartUp(HWND hwnd, int width, int height)
{
	// GdiplusStartup() : GDI+�� ����ϱ� ���� �ʼ� ȣ��
	Gdiplus::GdiplusStartupInput gsi;
	Gdiplus::GdiplusStartup(&g_GdiPlusToken, &gsi, nullptr);

	g_FrontBufferDC = GetDC(hwnd);							// ����Ʈ ���� DC�� ������ �ڵ�κ��� ������
	g_BackBufferDC = CreateCompatibleDC(g_FrontBufferDC);	// ����Ʈ ���� DC�� ȣȯ�Ǵ� �� ���� DC ����
	g_BackBufferBitmap = CreateCompatibleBitmap(g_FrontBufferDC, width, height);	// ����Ʈ ���ۿ� ���� ũ���� ��Ʈ�� ����
	SelectObject(g_BackBufferDC, g_BackBufferBitmap);		// �� ���� DC�� ��Ʈ�� ����
	g_pBackBufferGraphics = new Gdiplus::Graphics(g_BackBufferDC);					// GDI+ Graphics ��ü ����
}

void RenderManager::ShutDown(HWND hwnd)
{
	delete g_pBackBufferGraphics;		// GDI+ Graphics ��ü ����

	DeleteObject(g_BackBufferBitmap);	// ��Ʈ�� ����
	DeleteDC(g_BackBufferDC);			// �� ���� DC ����
	ReleaseDC(hwnd, g_FrontBufferDC);   // ����Ʈ ���� DC ����	
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

	Gdiplus::Pen pen(color, 2); // ��,� �׸��� 

	float left = box.m_Center.x - box.m_Extent.x;
	float top = box.m_Center.y - box.m_Extent.y;
	float width = box.m_Extent.x * 2;
	float height = box.m_Extent.y * 2;

	g_pBackBufferGraphics->DrawRectangle(&pen, left, top, width, height);
}

void RenderManager::DrawText_w(const std::wstring& text, float x, float y, float fontSize, Gdiplus::Color color)
{
	if (g_BackBufferDC == nullptr) return;

	// �ؽ�Ʈ ��¿� ����� GDI ��Ʈ ����
	LOGFONT logFont;
	ZeroMemory(&logFont, sizeof(LOGFONT));
	logFont.lfHeight = static_cast<int>(fontSize); // ��Ʈ ũ�� ����
	wcscpy_s(logFont.lfFaceName, L"Segoe UI");     // ����� ��Ʈ ����

	// GDI ��Ʈ ����
	HFONT hFont = CreateFontIndirect(&logFont);
	SelectObject(g_BackBufferDC, hFont); // DC�� ��Ʈ ����

	// �ؽ�Ʈ ���
	SetTextColor(g_BackBufferDC, RGB(color.GetRed(), color.GetGreen(), color.GetBlue())); // �ؽ�Ʈ ���� ����
	SetBkMode(g_BackBufferDC, TRANSPARENT); // ���� ����

	// �ؽ�Ʈ ���
	TextOut(g_BackBufferDC, static_cast<int>(x), static_cast<int>(y), text.c_str(), static_cast<int>(text.length()));

	// ��Ʈ ���ҽ� ����
	DeleteObject(hFont);
}