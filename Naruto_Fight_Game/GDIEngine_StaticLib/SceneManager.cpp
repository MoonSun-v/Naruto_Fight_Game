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
	// [ 다음 씬으로 변경 ]
	if (m_pNextScene)
	{
		if (m_pCurrentScene) m_pCurrentScene->Exit();

		m_pCurrentScene = m_pNextScene;
		m_pNextScene = nullptr;

		m_pCurrentScene->Enter();
	}

	// [ 현재 씬 업데이트 ]
	if (m_pCurrentScene) m_pCurrentScene->Update();
}

void SceneManager::Render()
{
	if (m_pCurrentScene) m_pCurrentScene->Render();
}

void SceneManager::ChangeScene(size_t index) // 벡터 크기 관련 함수는 전부 size_t를 반환
{
	if (index >= m_vScenes.size()) return;

	m_pNextScene = m_vScenes[index];
}
