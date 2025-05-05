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

void RenderManager::DrawImage(Gdiplus::Bitmap* g_pCurrentFrame_, float posX_, float posY_, float width_, float height_)
{
	Gdiplus::Rect destRect((int)posX_, (int)posY_, (int)width_, (int)height_);
	g_pBackBufferGraphics->DrawImage(g_pCurrentFrame_, destRect);
}

void RenderManager::DrawImageCenter(Gdiplus::Bitmap* bitmap, float centerX, float centerY)
{
	float x = centerX - bitmap->GetWidth() / 2.0f; 
	float y = centerY - bitmap->GetHeight() / 2.0f; 
	g_pBackBufferGraphics->DrawImage(bitmap, x, y);
}

void RenderManager::DrawImageClip(Gdiplus::Bitmap* bitmap, float x, float y, const Gdiplus::Rect& srcRect, bool flipX)
{
	if (!g_pBackBufferGraphics || !bitmap) return;

	Gdiplus::Matrix oldTransform;
	g_pBackBufferGraphics->GetTransform(&oldTransform); // ���� ��ȯ ����

	if (flipX)
	{
		Gdiplus::Matrix flipMatrix;
		flipMatrix.Scale(-1.0f, 1.0f); // �¿� ����

		float width = static_cast<float>(srcRect.Width);
		flipMatrix.Translate(-x * 2.0f - width, 0.0f); // ��ġ ����
		g_pBackBufferGraphics->SetTransform(&flipMatrix);
	}

	Gdiplus::Rect destRect((int)x, (int)y, srcRect.Width, srcRect.Height);
	g_pBackBufferGraphics->DrawImage(bitmap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel);

	if (flipX)
	{
		g_pBackBufferGraphics->SetTransform(&oldTransform); // ���� ���� ����
	}
}

void RenderManager::DrawImageClipWithColorKey(
	Gdiplus::Bitmap* bitmap,
	float x, float y,
	const Gdiplus::Rect& srcRect,
	Gdiplus::Color transparentColor,
	bool flipX)
{
	if (!g_pBackBufferGraphics || !bitmap) return;

	Gdiplus::ImageAttributes attr;
	attr.SetColorKey(transparentColor, transparentColor);

	Gdiplus::Matrix oldTransform;
	g_pBackBufferGraphics->GetTransform(&oldTransform);

	if (flipX)
	{
		Gdiplus::Matrix flipMatrix;
		float width = static_cast<float>(srcRect.Width);
		flipMatrix.Scale(-1.0f, 1.0f);
		flipMatrix.Translate(-x * 2.0f - width, 0.0f);
		g_pBackBufferGraphics->SetTransform(&flipMatrix);
	}

	Gdiplus::Rect destRect((int)x, (int)y, srcRect.Width, srcRect.Height);

	g_pBackBufferGraphics->DrawImage(
		bitmap,
		destRect,
		srcRect.X, srcRect.Y,
		srcRect.Width, srcRect.Height,
		Gdiplus::UnitPixel,
		&attr
	);

	if (flipX)
	{
		g_pBackBufferGraphics->SetTransform(&oldTransform);
	}
}

void RenderManager::DrawImageClipScaled(Gdiplus::Image* image, float x, float y,
	const Gdiplus::RectF& destRect, const Gdiplus::Rect& srcRect, bool flipX)
{
	if (!g_pBackBufferGraphics || !image) return;

	Gdiplus::Graphics* g = g_pBackBufferGraphics;

	if (flipX)
	{
		g->TranslateTransform(destRect.X + destRect.Width / 2, 0);
		g->ScaleTransform(-1, 1); // �¿� ����
		g->TranslateTransform(-destRect.X - destRect.Width / 2, 0);
	}

	g->DrawImage(image,
		destRect, // ������ ����
		static_cast<float>(srcRect.X),
		static_cast<float>(srcRect.Y),
		static_cast<float>(srcRect.Width),
		static_cast<float>(srcRect.Height),
		Gdiplus::UnitPixel);

	if (flipX)
		g->ResetTransform(); // ��ȯ �ʱ�ȭ
}

void RenderManager::DrawImageClipWithColorKeyScaled(Gdiplus::Image* image, float x, float y,
	const Gdiplus::RectF& destRect, const Gdiplus::Rect& srcRect,
	const Gdiplus::Color& transparentColor, bool flipX)
{
	if (!g_pBackBufferGraphics || !image) return;

	Gdiplus::Graphics* g = g_pBackBufferGraphics;

	// ���� Ű�� ���� �Ӽ� ����
	Gdiplus::ImageAttributes imgAttr;
	imgAttr.SetColorKey(transparentColor, transparentColor);

	if (flipX)
	{
		g->TranslateTransform(destRect.X + destRect.Width / 2, 0);
		g->ScaleTransform(-1, 1);
		g->TranslateTransform(-destRect.X - destRect.Width / 2, 0);
	}

	g->DrawImage(image,
		destRect,
		static_cast<float>(srcRect.X),
		static_cast<float>(srcRect.Y),
		static_cast<float>(srcRect.Width),
		static_cast<float>(srcRect.Height),
		Gdiplus::UnitPixel,
		&imgAttr);

	if (flipX)
		g->ResetTransform();
}
/*
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
*/
void RenderManager::DrawAABB(const AABB& box, Gdiplus::Color color, float scaleX /*= 1.0f*/, float scaleY /*= 1.0f*/)
{
	if (!g_pBackBufferGraphics) return;

	Gdiplus::Pen pen(color, 2); // �׵θ� �β�: 2

	// ������ ����� extent
	float scaledExtentX = box.m_Extent.x * scaleX;
	float scaledExtentY = box.m_Extent.y * scaleY;

	float left = box.m_Center.x - scaledExtentX;
	float top = box.m_Center.y - scaledExtentY;
	float width = scaledExtentX * 2;
	float height = scaledExtentY * 2;

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