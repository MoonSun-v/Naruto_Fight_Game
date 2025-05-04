#pragma once

#include "Object.h"
#include "Animator.h"
#include <gdiplus.h>

class Weapon : public Object
{
public:
public:
    Weapon() = default;  // 기본 생성자만 필요
    virtual ~Weapon();

    void Init(const std::wstring& atlasPath, const std::wstring& txtPath,
        const Vector2& pos, const Vector2& dir, bool flip);

    virtual void Update() override;
    virtual void Render() override;

    AABB GetAABB() const { return collider; }

private:
    void LoadAnimation(const std::wstring& txtPath);
    void UpdateCollider();

    Gdiplus::Bitmap* pBitmap = nullptr;

    Vector2 direction = Vector2(1.0f, 0.0f);  // 이동 방향
    float speed = 700.0f;                     // 픽셀/초
    bool flipX = false;                       // 좌우 반전 여부

    AABB collider;
    Animator animator;

    Gdiplus::Color transparentColor;          // 색상 키
};

