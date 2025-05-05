#include "framework.h"
#include "Background.h"

#include "RenderManager.h"

Background::Background(const std::wstring& imagePath)
{
    m_pBitmap = new Gdiplus::Bitmap(imagePath.c_str());
    if (m_pBitmap->GetLastStatus() != Gdiplus::Ok)
    {
        OutputDebugString(L"[ERROR] ��� �̹��� �ε� ����!\n");
    }
}

Background::~Background()
{
    delete m_pBitmap;
}

void Background::Render()
{
    if (m_pBitmap)
    {
        RenderManager::Get().DrawImage(m_pBitmap, 0, 0);  // ����� ȭ�� (0,0) ��ǥ�� �׸��ϴ�.
    }
}

void Background::Update()
{

}