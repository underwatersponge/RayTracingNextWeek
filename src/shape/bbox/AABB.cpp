#include "AABB.h"

AABB::AABB(const Interval& intervalX, const Interval& intervalY, const Interval& intervalZ):
	x(intervalX), y(intervalY), z(intervalZ){
	padToMinimums();
}

AABB::AABB(const Point3& a, const Point3& b)
{
	x = (a.x <= b.x ? Interval(a.x, b.x) : Interval(a.x, b.x));
	y = (a.y <= b.y ? Interval(a.y, b.y) : Interval(b.y, a.y));
	z = (a.z <= b.z ? Interval(a.z, b.z) : Interval(b.z, a.z));
	
	padToMinimums();
}

AABB::AABB(const AABB& bbox1, const AABB& bbox2)
{
	x = Interval(bbox1.x, bbox2.x);
	y = Interval(bbox1.y, bbox2.y);
	z = Interval(bbox1.z, bbox2.z);
}

const Interval& AABB::axisInterval(int id) const
{
	if (id == 1) return y;
	if (id == 2) return z;
	return x;
}

bool AABB::hit(const Ray& ray, Interval& rayT) const
{
	Point3 rayOrigion = ray.origion();
	Vec3 rayDir = ray.direction();

	for (int axis = 0; axis < 3; axis++) {
		const Interval& ax = axisInterval(axis);
		const float multipliter = 1.0 / rayDir[axis];

		float t0 = (ax.min - rayOrigion[axis]) * multipliter;
		float t1 = (ax.max - rayOrigion[axis]) * multipliter;

		if (t0 < t1) {
			if (t0 > rayT.min) rayT.min = t0;
			if (t1 < rayT.max) rayT.max = t1;
		}
		else {
			if (t1 > rayT.min) rayT.min = t1;
			if (t0 < rayT.max) rayT.max = t0;
		}

		if (rayT.max <= rayT.min) {
			return false;
		}
	}
	return true;
}

int AABB::longestAxis() const
{
	if (x.size() > y.size()) {
		return x.size() > z.size() ? 0 : 2;
	}
	else {
		return y.size() > z.size() ? 1 : 2;
	}

}

void AABB::padToMinimums()
{
	float delta = 0.00001;
	if (x.size() < delta) x.expand(delta);
	if (y.size() < delta) y.expand(delta);
	if (z.size() < delta) z.expand(delta);
}

const AABB AABB::empty = AABB(Interval::empty, Interval::empty, Interval::empty);
const AABB AABB::universe = AABB(Interval::universe, Interval::universe, Interval::universe);

AABB operator+(const AABB& bbox, const Vec3& offset)
{
	return AABB{ bbox.x + offset.x, bbox.y + offset.y, bbox.z + offset.z };
}

AABB operator+(const Vec3& offset, const AABB& bbox)
{
	return bbox + offset;
}
