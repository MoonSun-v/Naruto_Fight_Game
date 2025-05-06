#include "pch.h"
#include "Character.h"
#include "RenderManager.h" // 이렇게 해도 되는거구나..?!
#include "TimeManager.h"

#include <fstream>
#include <sstream>

Character::Character(const std::wstring& atlasPath, const std::wstring& txtPath)
{
    pBitmap = new Gdiplus::Bitmap(atlasPath.c_str());

    if (pBitmap->GetLastStatus() != Gdiplus::Ok)
        OutputDebugString(L"[ERROR] 아틀라스 이미지 로딩 실패!\n");
    else
        OutputDebugString(L"[SUCCESS] 아틀라스 이미지 로딩 성공!\n");

    LoadAnimation(txtPath);
}

Character::~Character()
{
    delete pBitmap;
}

void Character::LoadAnimation(const std::wstring& txtPath)
{
    std::wifstream file(txtPath);
    if (!file.is_open()) { OutputDebugString(L"[ERROR] .txt 파일 로딩 실패!\n"); return; }

    std::wstring line;
    while (std::getline(file, line))
    {
        std::wstringstream headerStream(line);
        std::wstring clipName;
        int frameCount;
        int loopFlag;

        headerStream >> clipName >> frameCount >> loopFlag;

        AnimationClip clip(loopFlag != 0); 

        for (int i = 0; i < frameCount; ++i)
        {
            std::getline(file, line);
            std::wstringstream frameStream(line);

            int l, t, r, b, offsetX, offsetY;
            wchar_t comma;
            frameStream >> l >> comma >> t >> comma >> r >> comma >> b >> comma >> offsetX >> comma >> offsetY;

            clip.AddFrame(Gdiplus::Rect(l, t, r - l, b - t), 0.1f); // 혹은 duration도 파일에 넣어도 됨
        }

        animator.AddClip(clipName, clip);
    }
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
    
    // 스케일 적용된 크기 계산
    float drawWidth = frame.Width * scale.x;
    float drawHeight = frame.Height * scale.y;

    Vector2 drawPos = position - Vector2(drawWidth / 2.0f, drawHeight / 2.0f);

    if (transparentColor.GetAlpha() == 0 &&
        transparentColor.GetRed() == 0 &&
        transparentColor.GetGreen() == 0 &&
        transparentColor.GetBlue() == 0)
    {
        RenderManager::Get().DrawImageClipScaled(
            pBitmap,
            drawPos.x, drawPos.y,
            Gdiplus::RectF(drawPos.x, drawPos.y, drawWidth, drawHeight), // 크기 조절
            frame,
            flipX
        );
    }
    else
    {
        RenderManager::Get().DrawImageClipWithColorKeyScaled(
            pBitmap,
            drawPos.x, drawPos.y,
            Gdiplus::RectF(drawPos.x, drawPos.y, drawWidth, drawHeight),
            frame,
            transparentColor,
            flipX
        );
    }

    // RenderManager::Get().DrawAABB(GetAABB(), Gdiplus::Color::Red, scale.x, scale.y);
}

void Character::UpdateCollider()
{
    const Gdiplus::Rect& rect = animator.GetCurrentFrameSourceRect();
    // collider.m_Center = position + Vector2(rect.Width / 2.0f, rect.Height / 2.0f);
    collider.m_Center = position; // 이미지 중심 기준
    // collider.m_Extent = Vector2(rect.Width / 2.0f, rect.Height / 2.0f);
    collider.m_Extent = Vector2(rect.Width * scale.x / 2.0f, rect.Height * scale.y / 2.0f);
}

void Character::SetTexture(const std::wstring& atlasPath)
{
    if (pBitmap)
    {
        delete pBitmap;
        pBitmap = nullptr;
    }

    pBitmap = new Gdiplus::Bitmap(atlasPath.c_str());

    if (pBitmap->GetLastStatus() != Gdiplus::Ok)
        OutputDebugString(L"[ERROR] 텍스처 교체 실패!\n");
    else
        OutputDebugString(L"[SUCCESS] 텍스처 교체 성공!\n");
}