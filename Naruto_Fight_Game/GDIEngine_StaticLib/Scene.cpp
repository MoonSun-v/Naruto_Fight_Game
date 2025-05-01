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
	for (auto& object : m_Objects) object->Update();
}

void Scene::Render()
{ 
	for (auto& object : m_Objects) object->Render();
}
