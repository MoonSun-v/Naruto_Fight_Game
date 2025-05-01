#pragma once

class Object;

class Scene
{
protected:
													//( list 보다 vector가 효율적임 )
	std::vector<Object*> m_Objects;					// 현재 씬에 존재하는 모든 오브젝트 목록
	std::vector<Object*> m_DeletePendingObjects;	// 나중에 삭제할 오브젝트 모아두는 임시 리스트

public:
	Scene() = default;
	virtual ~Scene()
	{
		Clear();
	}

	template<typename T>
	T* CreateObject()
	{
		T* pObject = new T();
		m_Objects.push_back(pObject);
		return pObject;
	}

	void Clear();

	virtual void Update();
	virtual void Render();
	virtual void Enter() {};
	virtual void Exit() { Clear(); }
};
