#include "pch.h"
#include "Animator.h"

// [ �̸� - �ִϸ��̼� Ŭ�� ���� ] : map ���� ��� 
void Animator::AddClip(const std::wstring& name, const AnimationClip& clip)
{
    m_Clips[name] = clip;
}

// [ ��� ] 
// forceRestart == false�̸� ���� �̸� �ִϸ��̼� �ߺ� ��� ����
void Animator::Play(const std::wstring& name, bool forceRestart)
{
    if (!forceRestart && m_CurrentClipName == name)
        return;

    auto it = m_Clips.find(name); // �̸����� ��ϵ� �ִϸ��̼� Ŭ���� ã�� 
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

    // ���� �������� duration�� �ʰ����� �� ���� ���������� �Ѿ
    while (m_ElapsedTime >= m_CurrentClip->frames[m_CurrentFrameIndex].duration)
    {
        m_ElapsedTime -= m_CurrentClip->frames[m_CurrentFrameIndex].duration;
        m_CurrentFrameIndex++;

        // ������ ������ ���� ó��
        if (m_CurrentFrameIndex >= m_CurrentClip->frames.size())
        {
            if (m_CurrentClip->isLoop)
                m_CurrentFrameIndex = 0;
            else
                m_CurrentFrameIndex = m_CurrentClip->frames.size() - 1;
        }
    }
}

// [ ���� ��� ���� �������� �ҽ� Rect ��ȯ ]
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

        OutputDebugString(log.c_str()); // ����� ���
    }
    */
    
    return m_CurrentClip &&
        !m_CurrentClip->isLoop &&
        m_CurrentFrameIndex == m_CurrentClip->frames.size() - 1;
        //&& m_ElapsedTime >= m_CurrentClip->frames.back().duration; 
    // �ӽ÷� isLoop�� false�� �ִϸ��̼��� ������ ���� �������� �ϳ� �� �߰��ؾ� �ڿ�������..
}