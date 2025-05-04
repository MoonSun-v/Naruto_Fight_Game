#include "framework.h"
#include "Weapon.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "Scene.h"

#include <fstream>
#include <sstream>

Weapon::~Weapon()
{
    delete pBitmap;
}

void Weapon::LoadAnimation(const std::wstring& txtPath)
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

            clip.AddFrame(Gdiplus::Rect(l, t, r - l, b - t), 0.1f);
        }

        animator.AddClip(clipName, clip);
    }
}

void Weapon::Init(const std::wstring& atlasPath, const std::wstring& txtPath,
    const Vector2& pos, const Vector2& dir, bool flip)
{
    if (pBitmap) delete pBitmap;

    pBitmap = new Gdiplus::Bitmap(atlasPath.c_str());
    transparentColor = Gdiplus::Color(0, 255, 0);

    if (pBitmap->GetLastStatus() != Gdiplus::Ok)
        OutputDebugString(L"[ERROR] 무기 이미지 로딩 실패!\n");

    LoadAnimation(txtPath);

    position = pos;
    direction = dir.Normalized();
    flipX = flip;
}

void Weapon::Update()
{
    float deltaTime = TimeManager::Get().GetDeltaTime();
    position += direction * speed * deltaTime;

    // 화면 밖으로 벗어나면 삭제 처리 : 이것도 잘 안됨
    if (position.x < 0 || position.x > 500 || position.y < 0 || position.y > 1080) {
        Scene* currentScene = SceneManager::Get().GetCurrentScene();
        currentScene->MarkForDelete(this);  // 무기가 화면 밖으로 나가면 삭제 대기
        return;
    }

    UpdateCollider();

    // 필요하면 충돌 검사 or 화면 벗어나면 삭제 처리 추가
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
    RenderManager::Get().DrawAABB(GetAABB());
}

void Weapon::UpdateCollider()
{
    const Gdiplus::Rect& rect = animator.GetCurrentFrameSourceRect();
    collider.m_Center = position + Vector2(rect.Width / 2.0f, rect.Height / 2.0f);
    collider.m_Extent = Vector2(rect.Width / 2.0f, rect.Height / 2.0f);
}
