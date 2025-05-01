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
