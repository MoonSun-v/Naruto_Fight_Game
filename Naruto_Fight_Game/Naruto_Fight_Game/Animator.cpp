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


bool Animator::IsAnimationFinished() const 
{
    /*
    if (m_CurrentClip) {
        std::wstring log = L"m_CurrentClip " + m_CurrentClipName + L"\n" +
            L"!m_CurrentClip->isLoop: " + std::to_wstring(!m_CurrentClip->isLoop) + L"\n" +
            L"m_CurrentFrameIndex == m_CurrentClip->frames.size() - 1 : " + std::to_wstring(m_CurrentFrameIndex == m_CurrentClip->frames.size() - 1) + L"\n" +
            L"m_ElapsedTime >= m_CurrentClip->frames.back().duration: " + std::to_wstring(m_ElapsedTime >= m_CurrentClip->frames.back().duration) + L"\n\n" ;

        OutputDebugString(log.c_str()); // 디버그 출력
    }
    */
    
    return m_CurrentClip &&
        !m_CurrentClip->isLoop &&
        m_CurrentFrameIndex == m_CurrentClip->frames.size() - 1;
        //&& m_ElapsedTime >= m_CurrentClip->frames.back().duration; 
    // 임시로 isLoop가 false인 애니메이션은 마지막 같은 프레임을 하나 더 추가해야 자연스러움..
}