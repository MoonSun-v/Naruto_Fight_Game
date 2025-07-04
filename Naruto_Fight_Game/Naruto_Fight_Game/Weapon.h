#pragma once

#include "Object.h"
#include "Animator.h"
#include "Player.h"
#include <gdiplus.h>

class Weapon : public Object
{
public:
    Weapon() = default;  
    virtual ~Weapon();

    void Init(const std::wstring& atlasPath, const std::wstring& txtPath,
        const Vector2& pos, const Vector2& dir, bool flip);

    virtual void Update() override;
    virtual void Render() override;

    AABB GetAABB() const { return collider; }
    void SetScale(const Vector2& s) { scale = s; }

    void SetOwner(Player* owner) { m_Owner = owner; }

private:
    Player* m_Owner = nullptr; // 무기 소유자 

    void LoadAnimation(const std::wstring& txtPath);
    void UpdateCollider();

    Gdiplus::Bitmap* pBitmap = nullptr;

    Vector2 direction = Vector2(1.0f, 0.0f);  // 이동 방향
    float speed = 700.0f;                     // 픽셀/초
    bool flipX = false;                       // 좌우 반전 여부

    AABB collider;
    Animator animator;

    Gdiplus::Color transparentColor;          // 색상 키
    Vector2 scale = { 1.7f, 1.7f };
};

