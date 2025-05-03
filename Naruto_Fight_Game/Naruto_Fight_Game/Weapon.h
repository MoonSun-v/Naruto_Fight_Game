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

    Vector2 direction = Vector2(1.0f, 0.0f);  // �̵� ����
    float speed = 400.0f;                     // �ȼ�/��
    bool flipX = false;                       // �¿� ���� ����

    Gdiplus::Color transparentColor;          // ���� Ű
};

