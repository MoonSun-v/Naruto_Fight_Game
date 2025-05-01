#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::StartUp()
{

}

void SceneManager::ShutDown()
{
	for (auto& scene : m_vScenes) delete scene;

	m_vScenes.clear();
}

void SceneManager::Update()
{
	// [ ���� ������ ���� ]
	if (m_pNextScene)
	{
		if (m_pCurrentScene) m_pCurrentScene->Exit();

		m_pCurrentScene = m_pNextScene;
		m_pNextScene = nullptr;

		m_pCurrentScene->Enter();
	}

	// [ ���� �� ������Ʈ ]
	if (m_pCurrentScene) m_pCurrentScene->Update();
}

void SceneManager::Render()
{
	if (m_pCurrentScene) m_pCurrentScene->Render();
}

void SceneManager::ChangeScene(size_t index) // ���� ũ�� ���� �Լ��� ���� size_t�� ��ȯ
{
	if (index >= m_vScenes.size()) return;

	m_pNextScene = m_vScenes[index];
}
