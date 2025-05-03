#pragma once

#include "Object.h"
#include "Vector2.h"
#include <GdiPlus.h>

class Weapon : public Object
{
public:
    Weapon(const std::wstring& imagePath, Gdiplus::Color transparent = Gdiplus::Color(0, 0, 0));
    virtual ~Weapon();

    void Init(const Vector2& pos, const Vector2& dir, bool flip = false);

    virtual void Update() override;
    virtual void Render() override;

private:
    Gdiplus::Bitmap* pBitmap = nullptr;

    Vector2 direction = Vector2(1.0f, 0.0f);  // 이동 방향
    float speed = 400.0f;                     // 픽셀/초
    bool flipX = false;                       // 좌우 반전 여부

    Gdiplus::Color transparentColor;          // 색상 키
};

