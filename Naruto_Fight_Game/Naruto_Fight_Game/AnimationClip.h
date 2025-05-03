#pragma once

// [ �ϳ��� ������ ���� ] (Ŭ�� ��ǥ + ���ӽð�)
struct AnimationFrame
{
    Gdiplus::Rect srcRect;
    float duration = 0.2f; // �ش� ������ ���� �ð� 

    // ��ǥ�κ��� �簢�� ����, ���ӽð� �⺻�� 0.1��
    AnimationFrame(int l, int t, int r, int b)
        : srcRect(l, t, r - l, b - t), duration(0.1f)
    {
    }

    // ��ǥ + ���ӽð� ����
    AnimationFrame(int l, int t, int r, int b, float d)
        : srcRect(l, t, r - l, b - t), duration(d)
    {
    }

    // �簢�� ��ü�� ���ӽð� ����
    AnimationFrame(const Gdiplus::Rect& rect, float d)
        : srcRect(rect), duration(d)
    {
    }
};

// [ �ִϸ��̼� ������ ���� ] (�ϳ��� �ִϸ��̼� Ŭ��)
class AnimationClip
{
public:
    std::vector<AnimationFrame> frames; // ������ ���
    bool isLoop = true;                 // true�� ��� �ִϸ��̼��� ���� �����
    float totalDuration = 0.0f;         // ��ü Ŭ���� ���ӽð� (������ ����)

    AnimationClip(bool loop = true) : isLoop(loop)
    {
    }
    // void SetLoop(bool loop) { isLoop = loop; }

    void AddFrame(const Gdiplus::Rect& rect, float duration)
    {
        frames.push_back({ rect, duration });   // ���ο� ������ �߰�
        totalDuration += duration;              // ��ü ���ӽð� ����
    }
};