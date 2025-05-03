#pragma once

#include <iostream>
#include <cmath>

using namespace std;

const float EPSILON = 1e-6f;  // 허용 오차 (0.000001)

class Vector2
{
public:
    float x, y;

    // 생성자
    Vector2(float x = 0.0f, float y = 0.0f);

    // 연산자 오버로딩
    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;

    Vector2& operator+=(const Vector2& rhs);
    Vector2& operator-=(const Vector2& rhs);

    // 벡터 연산 함수
    bool IsZero() const;
    float Dot(const Vector2& other) const;
    void Normalize();
    Vector2 Normalized() const;
    float Length() const;
    float LengthSQ() const;

    float Distance(const Vector2& other) const;

    // 출력 스트림 연산자
    friend ostream& operator<<(ostream& os, const Vector2& v);
};
