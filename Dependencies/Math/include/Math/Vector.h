#pragma once

#include <cmath>

class Vec2f {
public:
	float x, y;

	Vec2f() = default;
	explicit Vec2f(float v);
	Vec2f(float x, float y);
	Vec2f(const Vec2f &v);

	friend Vec2f operator+ (const Vec2f &a, const Vec2f &b);
	friend Vec2f operator+ (const Vec2f &a, float b);
	friend Vec2f operator- (const Vec2f &a, const Vec2f &b);
	friend Vec2f operator- (const Vec2f &a, float b);
	friend Vec2f operator* (const Vec2f &a, const Vec2f &b);
	friend Vec2f operator* (const Vec2f &a, float b);
	friend Vec2f operator/ (const Vec2f &a, const Vec2f &b);
	friend Vec2f operator/ (const Vec2f &a, float b);

	Vec2f& operator+= (Vec2f const &a);
	Vec2f& operator-= (Vec2f const &a);
	Vec2f& operator*= (float v);
	
	bool operator== (Vec2f &a) const;
	bool operator!= (Vec2f &a) const;

	Vec2f norm() const;
	float dot(Vec2f const &a) const;
	float len() const;
};

class Vec3f {
public:
	float x, y, z;

	Vec3f() = default;
	explicit Vec3f(float v);
	Vec3f(float x, float y, float z);
	Vec3f(const Vec2f& xy, float z);
	Vec3f(const Vec3f& v);

	Vec2f xy() const;
	Vec2f xz() const;
	Vec2f yz() const;

	friend Vec3f operator+ (const Vec3f &a, const Vec3f &b);
	friend Vec3f operator+ (const Vec3f &a, float b);
	friend Vec3f operator- (const Vec3f &a, const Vec3f &b);
	friend Vec3f operator- (const Vec3f &a, float b);
	friend Vec3f operator* (const Vec3f &a, const Vec3f &b);
	friend Vec3f operator* (const Vec3f &a, float b);
	friend Vec3f operator/ (const Vec3f &a, const Vec3f &b);
	friend Vec3f operator/ (const Vec3f &a, float b);

	Vec3f &operator+= (const Vec3f &a);
	Vec3f &operator-= (const Vec3f &a);
	Vec3f &operator*= (float v);
	
	bool operator== (Vec3f &a) const;
	bool operator!= (Vec3f &a) const;

	Vec3f cross(Vec3f const &a) const;
	Vec3f norm() const;
	float dot(Vec3f const &a) const;
	float len() const;
};

class Vec4f {
public:
    float x, y, z, w;

	Vec4f() = default;
    explicit Vec4f(float v);
    Vec4f(float x, float y, float z, float w);

    friend Vec4f operator+ (const Vec4f &a, const Vec4f &b);
    friend Vec4f operator+ (const Vec4f &a, float b);
    friend Vec4f operator- (const Vec4f &a, const Vec4f &b);
    friend Vec4f operator- (const Vec4f &a, float b);
    friend Vec4f operator* (const Vec4f &a, const Vec4f &b);
    friend Vec4f operator* (const Vec4f &a, float b);
    friend Vec4f operator/ (const Vec4f &a, const Vec4f &b);
    friend Vec4f operator/ (const Vec4f &a, float b);

    Vec4f &operator+= (const Vec4f &a);
    Vec4f &operator-= (const Vec4f &a);
    Vec4f &operator*= (float v);

    bool operator== (Vec4f &a) const;
    bool operator!= (Vec4f &a) const;
};