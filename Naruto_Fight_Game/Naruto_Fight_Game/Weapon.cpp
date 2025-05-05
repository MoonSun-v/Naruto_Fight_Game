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

    animator.Play(L"Kunai1");
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

void Weapon::Update()
{
    // __super::Update(); // 기본 무기 움직임

    float deltaTime = TimeManager::Get().GetDeltaTime();
    position += direction * speed * deltaTime;

    // 일정 영역 밖으로 벗어나면 삭제 처리 
    if (position.x < 0 || position.x > 1900 || position.y < 0 || position.y > 1080) {
        Scene* currentScene = SceneManager::Get().GetCurrentScene();
        currentScene->MarkForDelete(this);  // 무기가 화면 밖으로 나가면 삭제 대기
        return;
    }

    AABB myAABB = this->GetAABB();

    Scene* currentScene = SceneManager::Get().GetCurrentScene();
    const std::vector<Object*>& objects = currentScene->GetObjects();

    for (Object* target : objects)
    {
        if (target == this || target->IsPendingDelete())
            continue;

        Player* player = dynamic_cast<Player*>(target);
        if (!player) continue;

        if (player == m_Owner) continue; // 자기 자신은 무시

        AABB targetAABB = player->GetAABB();
        if (myAABB.CheckIntersect(targetAABB))
        {
            player->TakeDamage();

            currentScene->MarkForDelete(this); // 무기 삭제 예약
            break;
        }
    }

    UpdateCollider();

    // 충돌 검사
}

void Weapon::Render()
{
    if (!pBitmap) return;

    const Gdiplus::Rect& srcRect = animator.GetCurrentFrameSourceRect();

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

    // RenderManager::Get().DrawText_w(
    //    L"Collider Center: " + std::to_wstring(collider.m_Center.x), 150, 80, 20, Gdiplus::Color::Green);
}

void Weapon::UpdateCollider()
{
    const Gdiplus::Rect& rect = animator.GetCurrentFrameSourceRect();
    collider.m_Center = position + Vector2(rect.Width / 2.0f, rect.Height / 2.0f);
    collider.m_Extent = Vector2(rect.Width / 2.0f, rect.Height / 2.0f);
}
