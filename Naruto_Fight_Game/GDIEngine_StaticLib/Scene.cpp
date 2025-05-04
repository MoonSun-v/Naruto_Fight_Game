#include "pch.h"
#include "Scene.h"
#include "Object.h"

void Scene::Clear()
{
	for (auto& object : m_Objects) delete object;
	m_Objects.clear();

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

    // 1. 안전하게 복사해서 루프 돌리기
    std::vector<Object*> tempObjects = m_Objects;

    for (auto& object : tempObjects)
    {
        if (!object) continue;

        if (std::find(m_DeletePendingObjects.begin(), m_DeletePendingObjects.end(), object) != m_DeletePendingObjects.end())
            continue;

        // swprintf_s(buffer, L"[DEBUG] object addr: %p\n", object);
        // OutputDebugString(buffer);

        object->Update();
    }

    // 2. 삭제 예약된 객체 실제 삭제
    for (auto& obj : m_DeletePendingObjects)
    {
        auto it = std::find(m_Objects.begin(), m_Objects.end(), obj);
        if (it != m_Objects.end())
        {
            delete* it;
            m_Objects.erase(it);
        }
    }

    m_DeletePendingObjects.clear();
}

void Scene::Render()
{ 
	for (auto& object : m_Objects) object->Render();
}

void Scene::AddObject(Object* obj)
{
	m_Objects.push_back(obj);
}

void Scene::MarkForDelete(Object* obj)
{
    m_DeletePendingObjects.push_back(obj);
    /*
    // 중복 삽입 방지
    if (std::find(m_DeletePendingObjects.begin(), m_DeletePendingObjects.end(), obj) == m_DeletePendingObjects.end())
    {
        m_DeletePendingObjects.push_back(obj);
    }
    */
}