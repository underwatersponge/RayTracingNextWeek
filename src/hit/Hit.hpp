#pragma once
//#include "Vec3.hpp"
#include "../ray/Ray.hpp"
#include "../utility/Utility.hpp"
#include "../utility/Interval.h"
#include "../shape/bbox/AABB.h"

class Material;

struct HitInfo {
	Point3 p;
	Vec3 normal;
	float t;
	bool frontFace;
	std::shared_ptr<Material> material;
	float u;
	float v;


	void setFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
		frontFace = dot(ray.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class HitTable {
public:
	virtual ~HitTable() = default;

	virtual bool hit(const Ray& ray, Interval ray_t, HitInfo& rec) const = 0;
	
	virtual AABB boundingBox() const = 0;
};