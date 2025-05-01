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
    {
        OutputDebugString(L"[ERROR] ��Ʋ�� �̹��� �ε� ����!\n");
        return;
    }
    else
    {
        OutputDebugString(L"[ERROR] ��Ʋ�� �̹��� �ε� ����!\n");
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
        OutputDebugString(L"[ERROR] .mot ���� �ε� ����!\n");
        return;
    }
    else
    {
        OutputDebugString(L"[ERROR] .mot ���� �ε� ����!\n");
    }

    int frameCount = 0;
    file >> frameCount;

    for (int i = 0; i < frameCount; ++i)
    {
        int l, t, r, b, offsetX, offsetY;
        wchar_t comma;
        file >> l >> comma >> t >> comma >> r >> comma >> b >> comma >> offsetX >> comma >> offsetY;

        frames.emplace_back(l, t, r, b, 0.1f); // �⺻ 0.1�� per frame
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