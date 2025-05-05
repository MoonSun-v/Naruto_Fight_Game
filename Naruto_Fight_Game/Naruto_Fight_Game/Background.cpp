#include "framework.h"
#include "Background.h"

#include "RenderManager.h"

Background::Background(const std::wstring& imagePath)
{
    m_pBitmap = new Gdiplus::Bitmap(imagePath.c_str());
    if (m_pBitmap->GetLastStatus() != Gdiplus::Ok)
    {
        OutputDebugString(L"[ERROR] 배경 이미지 로딩 실패!\n");
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
        RenderManager::Get().DrawImage(m_pBitmap, 0, 0);  // 배경을 화면 (0,0) 좌표에 그립니다.
    }
}

void Background::Update()
{

}