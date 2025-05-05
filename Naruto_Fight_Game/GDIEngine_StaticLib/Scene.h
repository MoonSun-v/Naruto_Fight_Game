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

	// 오브젝트를 생성하고, 해당 오브젝트를 씬에 추가
	/*
	template<typename T>
	T* CreateObject()
	{
		T* pObject = new T();
		if (pObject) // 유효성 확인
			m_Objects.push_back(pObject);
		return pObject;
	}
	*/
	template<typename T, typename... Args>
	T* CreateObject(Args&&... args)
	{
		T* pObject = new T(std::forward<Args>(args)...);
		if (pObject)
			m_Objects.push_back(pObject);
		return pObject;
	}

	void Clear();

	virtual void Update();
	virtual void Render();
	virtual void Enter() {};
	virtual void Exit() { Clear(); }

	// 객체를 씬에 추가
	void AddObject(Object* obj) { m_Objects.push_back(obj); }

	// 삭제 예정 객체를 임시 리스트에 추가
	void MarkForDelete(Object* obj) { m_DeletePendingObjects.push_back(obj); }

	// 현재 씬에 있는 모든 객체를 반환
	const std::vector<Object*>& GetObjects() const { return m_Objects; }

};
