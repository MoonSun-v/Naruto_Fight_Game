#include "pch.h"
#include "Animator.h"

// [ 이름 - 애니메이션 클립 저장 ] : map 구조 사용 
void Animator::AddClip(const std::wstring& name, const AnimationClip& clip)
{
    m_Clips[name] = clip;
}

// [ 재생 ] 
// forceRestart == false이면 같은 이름 애니메이션 중복 재생 방지
void Animator::Play(const std::wstring& name, bool forceRestart)
{
    if (!forceRestart && m_CurrentClipName == name)
        return;

    auto it = m_Clips.find(name); // 이름으로 등록된 애니메이션 클립을 찾기 
    if (it != m_Clips.end())
    {
        m_CurrentClip = &it->second;
        m_CurrentClipName = name;
        m_CurrentFrameIndex = 0;
        m_ElapsedTime = 0.0f;
    }
}

void Animator::Stop()
{
    m_CurrentClip = nullptr;
    m_CurrentClipName.clear();
    m_CurrentFrameIndex = 0;
    m_ElapsedTime = 0.0f;
}

void Animator::Update(float deltaTime)
{
    if (!m_CurrentClip || m_CurrentClip->frames.empty())
        return;

    m_ElapsedTime += deltaTime;

    // 현재 프레임의 duration을 초과했을 때 다음 프레임으로 넘어감
    while (m_ElapsedTime >= m_CurrentClip->frames[m_CurrentFrameIndex].duration)
    {
        m_ElapsedTime -= m_CurrentClip->frames[m_CurrentFrameIndex].duration;
        m_CurrentFrameIndex++;

        // 마지막 프레임 이후 처리
        if (m_CurrentFrameIndex >= m_CurrentClip->frames.size())
        {
            if (m_CurrentClip->isLoop)
                m_CurrentFrameIndex = 0;
            else
                m_CurrentFrameIndex = m_CurrentClip->frames.size() - 1;
        }
    }
}

// [ 현재 재생 중인 프레임의 소스 Rect 반환 ]
const Gdiplus::Rect& Animator::GetCurrentFrameSourceRect() const
{
    static Gdiplus::Rect emptyRect(0, 0, 0, 0);

    if (!m_CurrentClip || m_CurrentClip->frames.empty())
        return emptyRect;

    return m_CurrentClip->frames[m_CurrentFrameIndex].srcRect;
}
