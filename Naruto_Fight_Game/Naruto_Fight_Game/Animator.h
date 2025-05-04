#pragma once
#include <unordered_map>
#include "AnimationClip.h"

// 현재 재생 중인 애니메이션 클립의 상태 관리
class Animator
{
private:
    std::unordered_map<std::wstring, AnimationClip> m_Clips;
    const AnimationClip* m_CurrentClip = nullptr;
    size_t m_CurrentFrameIndex = 0;
    float m_ElapsedTime = 0.0f;
    std::wstring m_CurrentClipName;

public:
    void AddClip(const std::wstring& name, const AnimationClip& clip);
    void Play(const std::wstring& name, bool forceRestart = false);
    void Stop();
    void Update(float deltaTime);
    const Gdiplus::Rect& GetCurrentFrameSourceRect() const;

    bool IsAnimationFinished() const;
};
