#pragma once
#include <iostream>
#include <cmath>
#include <limits>
#include "Utility.hpp"

class Vec3 {
public:
	Vec3():x(0.0), y(0.0), z(0.0){	}
	Vec3(float value): x(value), y(value), z(value){}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	float get_x()const { return x; }
	float get_y()const { return y; }
	float get_z()const { return z; }

	Vec3& operator+=(const Vec3& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	}
	
	Vec3& operator-=(const Vec3& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;

		return *this;
	}

	Vec3& operator*=(const Vec3& vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;

		return *this;
	}

	Vec3& operator/=(const Vec3& vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;

		return *this;
	}
	// uws
	float& operator[](int id) {
		if (id == 0) return x;
		if (id == 1) return y;
		if (id == 2) return z;
	}


	float lengthSquared()const {
		return x * x + y * y + z * z;
	}
	
	float length()const {
		return std::sqrt(lengthSquared());
	}

	bool nearZero()const {
		auto e = 1e-8;
		return(std::fabs(x) < e && std::fabs(y) < e && std::fabs(z) < e);
	}

	static Vec3 random() {
		return Vec3(randFloat(), randFloat(), randFloat());
	}
	static Vec3 random(float min, float max) {
		return Vec3(randFloat(min, max), randFloat(min, max), randFloat(min, max));
	}


public:
	float x;
	float y;
	float z;
};

// a alias of 
using Point3 = Vec3;

// vactor vector
inline std::ostream& operator<<(std::ostream& out, const Vec3& vel) {
	return out << vel.x << ' ' << vel.y << ' ' << vel.z << '\n';
}

inline Vec3 operator+ (const Vec3& vec1, const Vec3& vec2) {
	return Vec3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

inline Vec3 operator- (const Vec3& vec1, const Vec3& vec2) {
	return Vec3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

inline Vec3 operator* (const Vec3& vec1, const Vec3& vec2) {
	return Vec3(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}

inline Vec3 operator/ (const Vec3& vec1, const Vec3& vec2) {
	return Vec3(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
}

// vactor value

inline Vec3 operator+(const Vec3& vec, float value) {
	return Vec3(vec.x + value, vec.y + value, vec.z + value);
}

inline Vec3 operator+(float value, const Vec3& vec) {
	return Vec3(vec.x + value, vec.y + value, vec.z + value);
}

inline Vec3 operator*(const Vec3& vec, float value) {
	return Vec3(vec.x * value, vec.y * value, vec.z * value);
}

inline Vec3 operator*(float value, const Vec3& vec) {
	return Vec3(vec.x * value, vec.y * value, vec.z * value);
}

inline Vec3 operator/(const Vec3& vec, float value) {
	return vec * (1.0 / value);
}

inline Vec3 operator/(float value, const Vec3& vec) {
	return vec * (1.0 / value);
}

// utility 
inline Vec3 operator-(const Vec3& vec) {
	return Vec3(-vec.x, -vec.y, -vec.z);
}

inline float dot(const Vec3& vec1, const Vec3& vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

inline Vec3 cross(const Vec3& vec1, const Vec3& vec2) {
	return Vec3(
		vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x
	);
}

inline Vec3 unitVector(const Vec3& vec) {
	return vec / vec.length();
}

inline Vec3 randUnitVector() {
	while (true) {
		auto p = Vec3::random(-1, 1);
		auto lensq = p.lengthSquared();
		if (1e-40 < lensq && lensq <= 1.0) {
			return p / sqrt(lensq);
		}
	}
}

inline Vec3 randomOnHemisphere(const Vec3& normal) {
	auto dir = randUnitVector();
	if (dot(dir, normal) < 0.0) {
		return -dir;
	}
	return dir;
}

inline Vec3 randOnDisk() {
	while (true) {
		Vec3 p = Vec3(randFloat(-1.0, 1.0), randFloat(-1.0, 1.0), 0.0);
		if (p.lengthSquared() < 1.0) {
			return p;
		}
	}
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
	return (v - 2.0 * dot(v, n) * n);
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, float refIndexRatio) {
	float cosTheta = std::fmin(dot(-uv, n), 1.0);
	Vec3 perpendicular = refIndexRatio * (uv + cosTheta * n);
	Vec3 parallel = -std::sqrt(std::fabs(1.0 - perpendicular.lengthSquared())) * n;
	
	return perpendicular + parallel;
}