#pragma once
#include "../utility/Vec3.hpp"

class Ray {
public:
	Ray() {}// maybe not write like that <the tm maybe need expecity constructor>
	Ray(const Point3& origion, const Vec3 dir) : Origion(origion), Dir(dir), tm(0) {}

	Ray(const Point3& origion, const Vec3 dir, float time) : Origion(origion), Dir(dir), tm(time) {}


	const Point3& origion() const { return Origion; }
	const Vec3& direction() const { return Dir; }

	Point3 at(float move) const {
		return Origion + Dir * move;
	}

	float time()const { return tm; }

private:
	Point3 Origion;
	Vec3 Dir;
	float tm;
};
