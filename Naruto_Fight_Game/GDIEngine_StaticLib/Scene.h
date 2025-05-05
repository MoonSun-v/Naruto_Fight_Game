#pragma once

class Object;

class Scene
{
protected:
													//( list ���� vector�� ȿ������ )
	std::vector<Object*> m_Objects;					// ���� ���� �����ϴ� ��� ������Ʈ ���
	std::vector<Object*> m_DeletePendingObjects;	// ���߿� ������ ������Ʈ ��Ƶδ� �ӽ� ����Ʈ

public:
	Scene() = default;
	virtual ~Scene()
	{
		Clear();
	}

	// ������Ʈ�� �����ϰ�, �ش� ������Ʈ�� ���� �߰�
	/*
	template<typename T>
	T* CreateObject()
	{
		T* pObject = new T();
		if (pObject) // ��ȿ�� Ȯ��
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

	// ��ü�� ���� �߰�
	void AddObject(Object* obj) { m_Objects.push_back(obj); }

	// ���� ���� ��ü�� �ӽ� ����Ʈ�� �߰�
	void MarkForDelete(Object* obj) { m_DeletePendingObjects.push_back(obj); }

	// ���� ���� �ִ� ��� ��ü�� ��ȯ
	const std::vector<Object*>& GetObjects() const { return m_Objects; }

};
