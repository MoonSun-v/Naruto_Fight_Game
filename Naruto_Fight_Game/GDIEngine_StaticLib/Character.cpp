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
    {
        OutputDebugString(L"[ERROR] 아틀라스 이미지 로딩 실패!\n");
        return;
    }
    else
    {
        OutputDebugString(L"[ERROR] 아틀라스 이미지 로딩 성공!\n");
    }

    LoadAnimation(motPath);
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
    else
    {
        OutputDebugString(L"[ERROR] .mot 파일 로딩 성공!\n");
    }

    int frameCount = 0;
    file >> frameCount;

    for (int i = 0; i < frameCount; ++i)
    {
        int l, t, r, b, offsetX, offsetY;
        wchar_t comma;
        file >> l >> comma >> t >> comma >> r >> comma >> b >> comma >> offsetX >> comma >> offsetY;

        frames.emplace_back(l, t, r, b, 0.1f); // 기본 0.1초 per frame
    }

    file.close();
}

void Character::Update()
{
    float deltaTime = TimeManager::Get().GetDeltaTime();

    if (!frames.empty())
    {
        frameTimer += deltaTime;
        if (frameTimer >= frames[currentFrameIndex].duration)
        {
            frameTimer = 0.0f;
            currentFrameIndex = (currentFrameIndex + 1) % static_cast<int>(frames.size());
        }
    }

    UpdateCollider();
}

void Character::Render()
{
    if (!pBitmap || frames.empty()) return;

    const AnimationFrame& frame = frames[currentFrameIndex];

    RenderManager::Get().DrawImageClip(pBitmap, position.x, position.y, frame.srcRect);
    RenderManager::Get().DrawAABB(GetAABB());
}

void Character::UpdateCollider()
{
    if (!frames.empty())
    {
        auto& rect = frames[currentFrameIndex].srcRect;
        collider.m_Center = position + Vector2(rect.Width / 2.0f, rect.Height / 2.0f);
        collider.m_Extent = Vector2(rect.Width / 2.0f, rect.Height / 2.0f);
    }
}