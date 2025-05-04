#pragma once

#include "Object.h"
#include "Animator.h"
#include <gdiplus.h>

class Weapon : public Object
{
public:
public:
    Weapon() = default;  // �⺻ �����ڸ� �ʿ�
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

    Vector2 direction = Vector2(1.0f, 0.0f);  // �̵� ����
    float speed = 700.0f;                     // �ȼ�/��
    bool flipX = false;                       // �¿� ���� ����

    AABB collider;
    Animator animator;

    Gdiplus::Color transparentColor;          // ���� Ű
};

