#pragma once

// [ 싱글톤(Static) 클래스 ] 템플릿 클래스로 구현 
// 
// template <typename T> class Singleton
// T는 싱글톤으로 만들고 싶은 사용자 정의 클래스 타입. 
// 예: class GameManager : public Singleton<GameManager> {}

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

	// 복사 및 이동 금지 ( 복사 생성자 / 복사 대입 / 이동 생성자 / 이동 대입 전부 금지 )
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

	// [ 싱글톤 인스턴스 참조 반환 ] => 간접 호출 -> 없이 .으로 접근 
	// T& (참조)를 반환하기 때문에, 객체를 사용하는 것처럼 바로 접근 가능
	static T& Get()
	{
		assert(s_instance != nullptr && "Singleton instance not created!");
		return *s_instance;
	}

private:
	static T* s_instance; // 실제 싱글톤 객체 가리키는 정적 포인터
};


template <typename T>

T* Singleton<T>::s_instance = nullptr; // 정적 변수는 클래스 외부에서 반드시 정의 해줘야 함. 