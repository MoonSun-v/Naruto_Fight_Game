#include "pch.h"
#include "Vector2.h"

// 생성자
Vector2::Vector2(float x, float y) : x(x), y(y) {}

// + 더하기
Vector2 Vector2::operator+(const Vector2& rhs) const {

    return Vector2(x + rhs.x, y + rhs.y);
}

// - 빼기
Vector2 Vector2::operator-(const Vector2& rhs) const {

    return Vector2(x - rhs.x, y - rhs.y);
}

// * 스칼라 곱
Vector2 Vector2::operator*(float scalar) const {

    return Vector2(x * scalar, y * scalar);
}

// / 스칼라 나누기
Vector2 Vector2::operator/(float scalar) const {

    if (fabs(scalar) > EPSILON) {
        return Vector2(x / scalar, y / scalar);
    }
    return Vector2(0.0f, 0.0f); // 0에 가까운 값으로 나누는 경우 0 벡터 반환
}

// += 더하기 대입
Vector2& Vector2::operator+=(const Vector2& rhs) {

    x += rhs.x;
    y += rhs.y;
    return *this;
}

// -= 빼기 대입
Vector2& Vector2::operator-=(const Vector2& rhs) {

    x -= rhs.x;
    y -= rhs.y;
    return *this;
}


// 벡터의 길이가 0인지 확인
bool Vector2::IsZero() const {

    return fabs(x) < EPSILON && fabs(y) < EPSILON; // 부동소수점 오차 고려
}

// 벡터 내적 (Dot Product)
float Vector2::Dot(const Vector2& other) const {

    float dot = x * other.x + y * other.y;

    if (fabs(dot) < EPSILON) return 0.0f;           // 거의 0이면 0으로 보정
    if (fabs(dot - 1.0f) < EPSILON) return 1.0f;    // 거의 1이면 1로 보정
    if (fabs(dot + 1.0f) < EPSILON) return -1.0f;   // 거의 -1이면 -1로 보정

    return dot;
}

// 벡터 정규화 : 벡터 길이 1 , 방향 유지 
void Vector2::Normalize() {

    float length = Length();

    if (length > EPSILON) { // 부동소수점 오차 고려 : 길이가 0에 가까운 경우 정규화 X
        x /= length;
        y /= length;
    }
}

// 정규화된 복사본 반환
Vector2 Vector2::Normalized() const
{
    float length = Length();

    if (length > EPSILON)
        return Vector2(x / length, y / length);

    return Vector2(0.0f, 0.0f);
}


// 벡터 길이
float Vector2::Length() const {

    return sqrt(x * x + y * y);
}

// 벡터 길이의 제곱 
float Vector2::LengthSQ() const {

    return x * x + y * y;
}


// 두 벡터 간의 거리
float Vector2::Distance(const Vector2& other) const {

    float dx = x - other.x;
    float dy = y - other.y;
    float dist = dx * dx + dy * dy;

    if (dist < EPSILON) return 0.0f; // 부동소수점 오차 고려 : 거의 0인 경우 0으로 반환

    return sqrt(dist);
}


// 출력 연산자 (클래스 외부에서 구현) : 전역 함수 
ostream& operator<<(ostream& os, const Vector2& v) {

    os << "(" << v.x << ", " << v.y << ")";
    return os;
}