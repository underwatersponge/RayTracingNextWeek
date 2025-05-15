#pragma once

#include"../../utility/Interval.h"
#include "../../utility/Vec3.hpp"
#include "../../ray/Ray.hpp"

class AABB {
public:

	AABB() {};// wil call the default constructors of <x, y, z> 
	AABB(const Interval& intervalX, const Interval& intervalY, const Interval& intervalZ);
	AABB(const Point3& a, const Point3& b);
	AABB(const AABB& bbox1, const AABB& bbox2);


	const Interval& axisInterval(int id) const;

	bool hit(const Ray& ray, Interval& rayT)const;

	int longestAxis()const;

private:
	void padToMinimums();

public:
	Interval x, y, z;
public:
	static const AABB empty;
	static const AABB universe;
};

AABB operator+(const AABB& bbox, const Vec3& offset);

AABB operator+(const Vec3& offset, const AABB& bbox);