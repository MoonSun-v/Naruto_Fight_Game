#include "framework.h"
#include "Weapon.h"
#include "TimeManager.h"
#include "RenderManager.h"

Weapon::Weapon(const std::wstring& imagePath, Gdiplus::Color transparent)
    : transparentColor(transparent)
{
    pBitmap = new Gdiplus::Bitmap(imagePath.c_str());

    if (pBitmap->GetLastStatus() != Gdiplus::Ok)
        OutputDebugString(L"[ERROR] 무기 이미지 로딩 실패!\n");
    else
        OutputDebugString(L"[SUCCESS] 무기 이미지 로딩 성공!\n");
}

Weapon::~Weapon()
{
    delete pBitmap;
}

void Weapon::Init(const Vector2& pos, const Vector2& dir, bool flip)
{
    position = pos;
    direction = dir.Normalized();
    flipX = flip;
}

void Weapon::Update()
{
    float deltaTime = TimeManager::Get().GetDeltaTime();
    position += direction * speed * deltaTime;
}

void Weapon::Render()
{
    if (!pBitmap) return;

    Gdiplus::Rect srcRect(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());

    if (transparentColor.GetAlpha() == 0 &&
        transparentColor.GetRed() == 0 &&
        transparentColor.GetGreen() == 0 &&
        transparentColor.GetBlue() == 0)
    {
        RenderManager::Get().DrawImageClip(pBitmap, position.x, position.y, srcRect, flipX);
    }
    else
    {
        RenderManager::Get().DrawImageClipWithColorKey(pBitmap, position.x, position.y, srcRect, transparentColor, flipX);
    }
}
