#pragma once
#include "Object.h"

class Character : public Object
{
public:
    Character(const std::wstring& atlasPath, const std::wstring& motPath);
    virtual ~Character();

    virtual void Update() override;
    virtual void Render() override;

    AABB GetAABB() const { return collider; }

protected:
    void LoadAnimation(const std::wstring& motPath);
    virtual void UpdateCollider();

protected:
    float speed = 200.0f;

    struct AnimationFrame
    {
        Gdiplus::Rect srcRect;
        float duration;

        AnimationFrame(int l, int t, int r, int b, float dur)
            : srcRect(l, t, r - l, b - t), duration(dur) {
        }
    };

    std::vector<AnimationFrame> frames;
    int currentFrameIndex = 0;
    float frameTimer = 0.0f;

    Gdiplus::Bitmap* pBitmap = nullptr;
    AABB collider;
};