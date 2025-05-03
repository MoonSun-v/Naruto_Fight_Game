#pragma once

// [ 하나의 프레임 정보 ] (클립 좌표 + 지속시간)
struct AnimationFrame
{
    Gdiplus::Rect srcRect;
    float duration = 0.2f; // 해당 프레임 유지 시간 

    // 좌표로부터 사각형 생성, 지속시간 기본값 0.1초
    AnimationFrame(int l, int t, int r, int b)
        : srcRect(l, t, r - l, b - t), duration(0.1f)
    {
    }

    // 좌표 + 지속시간 지정
    AnimationFrame(int l, int t, int r, int b, float d)
        : srcRect(l, t, r - l, b - t), duration(d)
    {
    }

    // 사각형 객체와 지속시간 지정
    AnimationFrame(const Gdiplus::Rect& rect, float d)
        : srcRect(rect), duration(d)
    {
    }
};

// [ 애니메이션 프레임 묶음 ] (하나의 애니메이션 클립)
class AnimationClip
{
public:
    std::vector<AnimationFrame> frames; // 프레임 목록
    bool isLoop = true;                 // true일 경우 애니메이션을 루프 재생함
    float totalDuration = 0.0f;         // 전체 클립의 지속시간 (선택적 정보)

    AnimationClip(bool loop = true) : isLoop(loop)
    {
    }
    // void SetLoop(bool loop) { isLoop = loop; }

    void AddFrame(const Gdiplus::Rect& rect, float duration)
    {
        frames.push_back({ rect, duration });   // 새로운 프레임 추가
        totalDuration += duration;              // 전체 지속시간 누적
    }
};