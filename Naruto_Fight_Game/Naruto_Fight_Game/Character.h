#pragma once
#include "Object.h"
#include "Animator.h"
#include <gdiplus.h>

class Character : public Object
{
public:
    Character(const std::wstring& atlasPath, const std::wstring& txtPath);
    virtual ~Character();

    virtual void Update() override;
    virtual void Render() override;

    AABB GetAABB() const { return collider; }

    bool flipX = false;
    void SetFlipX(bool flip) { flipX = flip; }
    bool IsFlipX() const { return flipX; }

protected:
    void LoadAnimation(const std::wstring& txtPath);
    virtual void UpdateCollider();

    Gdiplus::Bitmap* pBitmap = nullptr;
    AABB collider;
    Animator animator;

    // 0이면 투명색 없음, 아니면 사용
    Gdiplus::Color transparentColor = Gdiplus::Color(0, 0, 0, 0);
};