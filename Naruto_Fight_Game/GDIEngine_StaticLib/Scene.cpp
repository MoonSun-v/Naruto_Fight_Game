#include "pch.h"
#include "Scene.h"
#include "Object.h"

void Scene::Clear()
{
    // 모든 객체 삭제 
	for (auto& object : m_Objects) delete object;
	m_Objects.clear();

    // 삭제 예정 객체 삭제 
	for (auto& object : m_DeletePendingObjects) delete object;
	m_DeletePendingObjects.clear();
}

void Scene::Update()
{
    // 디버그 출력
    /*
    wchar_t buffer[256];
    swprintf_s(buffer, L"[DEBUG] m_Objects Count: %d\n", static_cast<int>(m_Objects.size()));
    OutputDebugString(buffer);

    for (size_t i = 0; i < m_Objects.size(); ++i)
    {
        swprintf_s(buffer, L"  [%zu] Addr: %p\n", i, m_Objects[i]);
        OutputDebugString(buffer);
    }
    */

    // 객체들에 대해 안전하게 복사본을 만들어서 업데이트
    std::vector<Object*> tempObjects = m_Objects;

    for (auto& object : tempObjects)
    {
        if (!object) continue;

        if (object->IsPendingDelete()) continue;  // 삭제 예약된 객체는 건너뜀

        // swprintf_s(buffer, L"[DEBUG] object addr: %p\n", object);
        // OutputDebugString(buffer);

        object->Update();
    }

    // [ 삭제 예약된 객체 실제 삭제 ]
    for (auto& obj : m_DeletePendingObjects)
    {
        auto it = std::find(m_Objects.begin(), m_Objects.end(), obj);
        if (it != m_Objects.end())
        {
            delete* it; // 객체 삭제
            m_Objects.erase(it); // 리스트에서 객체 제거
        }
    }

    m_DeletePendingObjects.clear(); // 삭제 예정 객체들 리스트 초기화
}

// [ 씬에 존재하는 객체들 렌더링 ]
void Scene::Render()
{ 
	for (auto& object : m_Objects) object->Render();
}