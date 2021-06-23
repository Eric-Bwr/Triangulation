#pragma once

#include <cstdio>
#include <cmath>
#include "Vector.h"

class Mat4f {
public:
    float m00 = 0.0f;
    float m01 = 0.0f;
    float m02 = 0.0f;
    float m03 = 0.0f;
    float m10 = 0.0f;
    float m11 = 0.0f;
    float m12 = 0.0f;
    float m13 = 0.0f;
    float m20 = 0.0f;
    float m21 = 0.0f;
    float m22 = 0.0f;
    float m23 = 0.0f;
    float m30 = 0.0f;
    float m31 = 0.0f;
    float m32 = 0.0f;
    float m33 = 0.0f;
    float* buffer = new float[16] {m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33};

    Mat4f() = default;
    explicit Mat4f(float v);

    Mat4f &identity();
    Mat4f &translate(const Vec3f &vector);
    Mat4f &translate(float x, float y, float z);
    Mat4f &rotate(float angle, const Vec3f &axis);
    Mat4f &rotate(float angle, float x, float y, float z);
    Mat4f &scale(float scale);
    Mat4f &scale(float x, float y, float z);
    Mat4f &scale(const Vec3f &scale);
    Mat4f &multiply(const Mat4f& matrix);
    Mat4f &multiply(const Mat4f& one, const Mat4f& two);
    Mat4f &invert();
    Mat4f &removeTranslation();
    Mat4f &orthographic(float left, float right, float bottom, float top, float near, float far);
    Mat4f &perspective(float fov, float width, float height, float near, float far);
    Mat4f &lookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up);

    char *toString() const;
    float* getBuffer() const;
    void updateBuffer();

    ~Mat4f();
};

Mat4f identityMatrix();
Mat4f perspectiveMatrix(float fov, float width, float height, float near, float far);
Mat4f orthographicMatrix(float left, float right, float bottom, float top, float near, float far);
Mat4f lookAtMatrix(const Vec3f &eye, const Vec3f &center, const Vec3f &up);
