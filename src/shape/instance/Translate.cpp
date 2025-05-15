#include "Translate.h"

Translate::Translate(std::shared_ptr<HitTable> obj, const Vec3& offset):
	obj(obj), offset(offset)
{
	bbox = obj->boundingBox() + offset;
}

bool Translate::hit(const Ray& ray, Interval rayT, HitInfo& rec) const
{
	Ray offsetRay = { ray.origion() - offset, ray.direction(), ray.time()};
	if (!obj->hit(offsetRay, rayT, rec)) {
		return false;
	}

	rec.p += offset;
	return true;

}

AABB Translate::boundingBox() const
{
	return bbox;
}
