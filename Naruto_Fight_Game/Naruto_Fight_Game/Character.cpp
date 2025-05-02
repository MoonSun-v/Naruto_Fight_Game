#include "pch.h"
#include "Character.h"
#include "RenderManager.h" // 이렇게 해도 되는거구나..?!
#include "TimeManager.h"

#include <fstream>
#include <sstream>

Character::Character(const std::wstring& atlasPath, const std::wstring& motPath)
{
    pBitmap = new Gdiplus::Bitmap(atlasPath.c_str());

    if (pBitmap->GetLastStatus() != Gdiplus::Ok)
        OutputDebugString(L"[ERROR] 아틀라스 이미지 로딩 실패!\n");
    else
        OutputDebugString(L"[SUCCESS] 아틀라스 이미지 로딩 성공!\n");

    LoadAnimation(motPath);
    animator.Play(L"Idle"); // 기본 재생
}

Character::~Character()
{
    delete pBitmap;
}

void Character::LoadAnimation(const std::wstring& motPath)
{
    std::wifstream file(motPath);
    if (!file.is_open())
    {
        OutputDebugString(L"[ERROR] .mot 파일 로딩 실패!\n");
        return;
    }

    int frameCount = 0;
    file >> frameCount;

    AnimationClip idleClip;

    for (int i = 0; i < frameCount; ++i)
    {
        int l, t, r, b, offsetX, offsetY;
        wchar_t comma;
        file >> l >> comma >> t >> comma >> r >> comma >> b >> comma >> offsetX >> comma >> offsetY;

        idleClip.AddFrame(Gdiplus::Rect(l, t, r - l, b - t), 0.1f);
    }

    animator.AddClip(L"Idle", idleClip);
    animator.Play(L"Idle");

    file.close();
}

void Character::Update()
{
    float deltaTime = TimeManager::Get().GetDeltaTime();
    animator.Update(deltaTime);

    UpdateCollider();
}

void Character::Render()
{
    if (!pBitmap) return;

    const Gdiplus::Rect& frame = animator.GetCurrentFrameSourceRect();

    if (transparentColor.GetAlpha() == 0 &&
        transparentColor.GetRed() == 0 &&
        transparentColor.GetGreen() == 0 &&
        transparentColor.GetBlue() == 0)
    {
        RenderManager::Get().DrawImageClip(pBitmap, position.x, position.y, frame);
    }
    else
    {
        RenderManager::Get().DrawImageClipWithColorKey(pBitmap, position.x, position.y, frame, transparentColor);
    }

    RenderManager::Get().DrawAABB(GetAABB());
}

void Character::UpdateCollider()
{
    const Gdiplus::Rect& rect = animator.GetCurrentFrameSourceRect();
    collider.m_Center = position + Vector2(rect.Width / 2.0f, rect.Height / 2.0f);
    collider.m_Extent = Vector2(rect.Width / 2.0f, rect.Height / 2.0f);
}