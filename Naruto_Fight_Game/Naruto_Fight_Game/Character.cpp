#include "pch.h"
#include "Character.h"
#include "RenderManager.h" // �̷��� �ص� �Ǵ°ű���..?!
#include "TimeManager.h"

#include <fstream>
#include <sstream>

Character::Character(const std::wstring& atlasPath, const std::wstring& motPath)
{
    pBitmap = new Gdiplus::Bitmap(atlasPath.c_str());

    if (pBitmap->GetLastStatus() != Gdiplus::Ok)
        OutputDebugString(L"[ERROR] ��Ʋ�� �̹��� �ε� ����!\n");
    else
        OutputDebugString(L"[SUCCESS] ��Ʋ�� �̹��� �ε� ����!\n");

    LoadAnimation(motPath);
    animator.Play(L"Idle"); // �⺻ ���
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
        OutputDebugString(L"[ERROR] .mot ���� �ε� ����!\n");
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