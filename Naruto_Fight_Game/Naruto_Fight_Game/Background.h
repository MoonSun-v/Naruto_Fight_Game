#pragma once
#include "Object.h"
#include <gdiplus.h>

class Background : public Object
{
private:
    Gdiplus::Bitmap* m_pBitmap;

public:
    Background(const std::wstring& imagePath);
    ~Background();

    virtual void Update() override;
    virtual void Render() override;
};