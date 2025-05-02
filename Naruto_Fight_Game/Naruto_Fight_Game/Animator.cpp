#include "pch.h"
#include "Animator.h"

void Animator::AddClip(const std::wstring& name, const AnimationClip& clip)
{
    m_Clips[name] = clip;
}

void Animator::Play(const std::wstring& name, bool forceRestart)
{
    if (!forceRestart && m_CurrentClipName == name)
        return;

    auto it = m_Clips.find(name);
    if (it != m_Clips.end())
    {
        m_CurrentClip = &it->second;
        m_CurrentClipName = name;
        m_CurrentFrameIndex = 0;
        m_ElapsedTime = 0.0f;
    }
}

void Animator::Update(float deltaTime)
{
    if (!m_CurrentClip || m_CurrentClip->frames.empty())
        return;

    m_ElapsedTime += deltaTime;

    while (m_ElapsedTime >= m_CurrentClip->frames[m_CurrentFrameIndex].duration)
    {
        m_ElapsedTime -= m_CurrentClip->frames[m_CurrentFrameIndex].duration;
        m_CurrentFrameIndex++;

        if (m_CurrentFrameIndex >= m_CurrentClip->frames.size())
        {
            if (m_CurrentClip->isLoop)
                m_CurrentFrameIndex = 0;
            else
                m_CurrentFrameIndex = m_CurrentClip->frames.size() - 1;
        }
    }
}

const Gdiplus::Rect& Animator::GetCurrentFrameSourceRect() const
{
    static Gdiplus::Rect emptyRect(0, 0, 0, 0);

    if (!m_CurrentClip || m_CurrentClip->frames.empty())
        return emptyRect;

    return m_CurrentClip->frames[m_CurrentFrameIndex].srcRect;
}

void Animator::SetFlipX(bool flip)
{
    m_bFlipX = flip;
}

