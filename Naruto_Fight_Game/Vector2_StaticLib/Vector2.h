#pragma once

#include <iostream>
#include <cmath>

using namespace std;

const float EPSILON = 1e-6f;  // ��� ���� (0.000001)

class Vector2
{
public:
    float x, y;

    // ������
    Vector2(float x = 0.0f, float y = 0.0f);

    // ������ �����ε�
    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;

    Vector2& operator+=(const Vector2& rhs);
    Vector2& operator-=(const Vector2& rhs);

    // ���� ���� �Լ�
    bool IsZero() const;
    float Dot(const Vector2& other) const;
    void Normalize();
    Vector2 Normalized() const;
    float Length() const;
    float LengthSQ() const;

    float Distance(const Vector2& other) const;

    // ��� ��Ʈ�� ������
    friend ostream& operator<<(ostream& os, const Vector2& v);
};
