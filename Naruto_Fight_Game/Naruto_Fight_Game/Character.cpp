#include "pch.h"
#include "Character.h"
#include "RenderManager.h" // �̷��� �ص� �Ǵ°ű���..?!
#include "TimeManager.h"

#include <fstream>
#include <sstream>

Character::Character(const std::wstring& atlasPath, const std::wstring& txtPath)
{
    pBitmap = new Gdiplus::Bitmap(atlasPath.c_str());

    if (pBitmap->GetLastStatus() != Gdiplus::Ok)
        OutputDebugString(L"[ERROR] ��Ʋ�� �̹��� �ε� ����!\n");
    else
        OutputDebugString(L"[SUCCESS] ��Ʋ�� �̹��� �ε� ����!\n");

    LoadAnimation(txtPath);
}

Character::~Character()
{
    delete pBitmap;
}

void Character::LoadAnimation(const std::wstring& txtPath)
{
    std::wifstream file(txtPath);
    if (!file.is_open()) { OutputDebugString(L"[ERROR] .txt ���� �ε� ����!\n"); return; }

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

            clip.AddFrame(Gdiplus::Rect(l, t, r - l, b - t), 0.1f); // Ȥ�� duration�� ���Ͽ� �־ ��
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
    
    // ������ ����� ũ�� ���
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
            Gdiplus::RectF(drawPos.x, drawPos.y, drawWidth, drawHeight), // ũ�� ����
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
    collider.m_Center = position; // �̹��� �߽� ����
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
        OutputDebugString(L"[ERROR] �ؽ�ó ��ü ����!\n");
    else
        OutputDebugString(L"[SUCCESS] �ؽ�ó ��ü ����!\n");
}