#pragma once
#include "../hit/Hit.hpp"
#include "../utility/Vec3.hpp"

class Sphere : public HitTable{
public:
	Sphere()= default;
	// stationary sphere
	Sphere(const Point3& staticCenter, float radius, std::shared_ptr<Material> mat) :
		center(staticCenter, Vec3(0.0, 0.0, 0.0)), radius(std::fmax(0.0, radius)), material(mat)
	{
		Vec3 vel{ radius, radius, radius };
		bbox = AABB(Point3(staticCenter - vel), Point3(staticCenter + vel));
	}
	
	// moving sphere
	Sphere(const Point3& center1, const Point3& center2, float radius, std::shared_ptr<Material> mat) :
		center(center1, center2 - center1), radius(std::fmax(0.0, radius)), material(mat)
	{
		Vec3 vel{ radius, radius, radius };
		//AABB box1{ center1 - vel, center1 + vel };
		//AABB box2{ center2 - vel, center2 + vel };

		AABB box1{ center.at(0.0) - vel, center.at(0.0) + vel };
		AABB box2{ center.at(1.0) - vel, center.at(1.0) + vel };

		bbox = AABB(box1, box2);
	}

	Sphere(const Sphere& sphere):center(sphere.center), radius(sphere.radius), material(sphere.material), bbox(sphere.bbox){}

	// solver a quadratic 
	bool hit(const Ray& ray, Interval t, HitInfo& rec)const override;

	void getSphereUV(const Point3& p, float& u, float& v)const;

	AABB boundingBox()const override {
		return bbox;
	}

private:
	Ray center;
	float radius;
	std::shared_ptr<Material> material;
	AABB bbox;
};