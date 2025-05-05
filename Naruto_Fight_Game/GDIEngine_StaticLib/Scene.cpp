#include "pch.h"
#include "Scene.h"
#include "Object.h"

void Scene::Clear()
{
    // ��� ��ü ���� 
	for (auto& object : m_Objects) delete object;
	m_Objects.clear();

    // ���� ���� ��ü ���� 
	for (auto& object : m_DeletePendingObjects) delete object;
	m_DeletePendingObjects.clear();
}

void Scene::Update()
{
    // ����� ���
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

    // ��ü�鿡 ���� �����ϰ� ���纻�� ���� ������Ʈ
    std::vector<Object*> tempObjects = m_Objects;

    for (auto& object : tempObjects)
    {
        if (!object) continue;

        if (object->IsPendingDelete()) continue;  // ���� ����� ��ü�� �ǳʶ�

        // swprintf_s(buffer, L"[DEBUG] object addr: %p\n", object);
        // OutputDebugString(buffer);

        object->Update();
    }

    // [ ���� ����� ��ü ���� ���� ]
    for (auto& obj : m_DeletePendingObjects)
    {
        auto it = std::find(m_Objects.begin(), m_Objects.end(), obj);
        if (it != m_Objects.end())
        {
            delete* it; // ��ü ����
            m_Objects.erase(it); // ����Ʈ���� ��ü ����
        }
    }

    m_DeletePendingObjects.clear(); // ���� ���� ��ü�� ����Ʈ �ʱ�ȭ
}

// [ ���� �����ϴ� ��ü�� ������ ]
void Scene::Render()
{ 
	for (auto& object : m_Objects) object->Render();
}