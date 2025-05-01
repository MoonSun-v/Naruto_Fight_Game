#pragma once

// [ �̱���(Static) Ŭ���� ] ���ø� Ŭ������ ���� 
// 
// template <typename T> class Singleton
// T�� �̱������� ����� ���� ����� ���� Ŭ���� Ÿ��. 
// ��: class GameManager : public Singleton<GameManager> {}

template <typename T>

class Singleton 
{
public:
	Singleton()
	{
		assert(s_instance == nullptr && "Singleton instance already created!");
		s_instance = static_cast<T*>(this);
	}

	virtual ~Singleton() = default;

	// ���� �� �̵� ���� ( ���� ������ / ���� ���� / �̵� ������ / �̵� ���� ���� ���� )
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

	// [ �̱��� �ν��Ͻ� ���� ��ȯ ] => ���� ȣ�� -> ���� .���� ���� 
	// T& (����)�� ��ȯ�ϱ� ������, ��ü�� ����ϴ� ��ó�� �ٷ� ���� ����
	static T& Get()
	{
		assert(s_instance != nullptr && "Singleton instance not created!");
		return *s_instance;
	}

private:
	static T* s_instance; // ���� �̱��� ��ü ����Ű�� ���� ������
};


template <typename T>

T* Singleton<T>::s_instance = nullptr; // ���� ������ Ŭ���� �ܺο��� �ݵ�� ���� ����� ��. 