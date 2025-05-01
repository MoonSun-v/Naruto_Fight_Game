#pragma once
#include "Object.h"

class Character : public Object
{

public:
    struct AnimationFrame
    {
        Gdiplus::Rect srcRect; // �̹��� �߶� �κ�
        float duration;        // ��� �ð� (��)

        AnimationFrame(int l, int t, int r, int b, float dur)
            : srcRect(l, t, r - l, b - t), duration(dur) {
        }
    };

public:
    Character(const std::wstring& atlasPath, const std::wstring& motPath);
    virtual ~Character();

    void Update() override;
    void Render() override;

protected:
    void LoadAnimation(const std::wstring& motPath);

    Gdiplus::Bitmap* pBitmap = nullptr;
    std::vector<AnimationFrame> frames;
    int currentFrameIndex = 0;
    float frameTimer = 0.0f;


};