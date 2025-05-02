#pragma once

// �ϳ��� ������ ���� (Ŭ�� ��ǥ + ���ӽð�)
struct AnimationFrame
{
    Gdiplus::Rect srcRect;
    float duration = 0.1f;

    AnimationFrame(int l, int t, int r, int b)
        : srcRect(l, t, r - l, b - t), duration(0.1f)
    {
    }

    AnimationFrame(int l, int t, int r, int b, float d)
        : srcRect(l, t, r - l, b - t), duration(d)
    {
    }

    AnimationFrame(const Gdiplus::Rect& rect, float d)
        : srcRect(rect), duration(d)
    {
    }
};

// ������ ���� ����
class AnimationClip
{
public:

    std::vector<AnimationFrame> frames;
    bool isLoop = true;
    float totalDuration = 0.0f;

    void AddFrame(const Gdiplus::Rect& rect, float duration)
    {
        frames.push_back({ rect, duration });
        totalDuration += duration;
    }
};