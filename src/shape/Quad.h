#pragma once
#include "../hit/Hit.hpp"
#include "../mat/MaterialBase.h"
#include "HitTableList.h"
#include <memory>

class Quad : public HitTable{
public:
	Quad(Point3 Q, Vec3 u, Vec3 v, std::shared_ptr<Material> mat);

	virtual void setBoundingBox();

	AABB boundingBox()const override;
	bool hit(const Ray& ray, Interval rayT, HitInfo& rec)const override;
	
	virtual bool isInterior(float a, float b, HitInfo& rec) const;

private:
	Point3 Q;
	Vec3 u;
	Vec3 v;
	std::shared_ptr<Material> mat;
	AABB bbox;
	Vec3 normal;
	float D;
	Vec3 w;
};

inline std::shared_ptr<HitTableList> box(const Point3& a, const Point3& b, std::shared_ptr<Material> mat) {
	using std::make_shared;

	auto sides = make_shared<HitTableList>();
	
	auto min = Point3(std::fmin(a.x, b.x), std::fmin(a.y, b.y), std::fmin(a.z, b.z));
	auto max = Point3(std::fmax(a.x, b.x), std::fmax(a.y, b.y), std::fmax(a.x, b.z));

	auto dx = Vec3(max.x - min.x, 0.0, 0.0);
	auto dy = Vec3(0.0, max.y - min.y, 0.0);
	auto dz = Vec3(0.0, 0.0, max.z - min.z);

	sides->add(make_shared<Quad>(Point3(min.x, min.y, max.z), dx, dy, mat));// front
	sides->add(make_shared<Quad>(Point3(max.x, min.y, max.z), -dz, dy, mat));//right
	sides->add(make_shared<Quad>(Point3(max.x, min.y, min.z), -dx, dy, mat));// back
	sides->add(make_shared<Quad>(Point3(min.x, min.y, min.z), dz, dy, mat));// left
	sides->add(make_shared<Quad>(Point3(min.x, max.y, max.z), dx, -dz, mat));// top
	sides->add(make_shared<Quad>(Point3(min.x, min.y, min.z), dx, dz, mat));//bottom

	return sides;
}