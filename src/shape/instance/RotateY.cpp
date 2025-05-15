#include "RotateY.h"

rotateY::rotateY(std::shared_ptr<HitTable> obj, float angle):
	obj(obj)
{
	float radians = degreeToRadians(angle);
	sinTheta = std::sin(radians);
	cosTheta = std::cos(radians);
	bbox = obj->boundingBox();

	Point3 min(infinity, infinity, infinity);
	Point3 max(-infinity, -infinity, -infinity);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				auto x = i * bbox.x.max + (1 - i) * bbox.x.min;
				auto y = j * bbox.y.max + (1 - j) * bbox.y.min;
				auto z = k * bbox.z.max + (1 - k) * bbox.z.min;

				auto newx = cosTheta * x + sinTheta * z;
				auto newz = -sinTheta * x + cosTheta * z;

				Vec3 tester{ newx, y, newz };

				for (int c = 0; c < 3; c++) {
					min[c] = std::fmin(min[c], tester[c]);
					max[c] = std::fmin(max[c], tester[c]);
				}

			}
		}
	}
	bbox = AABB(min, max);
}

bool rotateY::hit(const Ray& ray, Interval rayT, HitInfo& rec) const
{
	auto origion = Point3(
		cosTheta * ray.origion().x - sinTheta * ray.origion().z,
		ray.origion().y,
		sinTheta * ray.origion().x + cosTheta * ray.origion().z
	);

	auto direction = Point3(
		cosTheta * ray.direction().x - sinTheta * ray.direction().z,
		ray.direction().y,
		sinTheta * ray.direction().x + cosTheta * ray.direction().z
	);
	
	Ray rotatedRay(origion, direction, ray.time());

	if (!obj->hit(rotatedRay, rayT, rec)) {
		return false;
	}

	//if (!obj->hit(rotatedRay, rayT, rec))
	//	return false;

	rec.p = Point3(
		cosTheta * rec.p.x + sinTheta * rec.p.z,
		rec.p.y,
		-sinTheta * rec.p.x + cosTheta * rec.p.z
	);

	rec.normal = Point3(
		cosTheta * rec.normal.x + sinTheta * rec.normal.z,
		rec.normal.y,
		-sinTheta * rec.normal.x + cosTheta * rec.normal.z
	);

	return true;
}

AABB rotateY::boundingBox() const
{
	return bbox;
}
