#pragma once
#include "../../hit/Hit.hpp"

class rotateY : public HitTable {
public:
	rotateY(std::shared_ptr<HitTable> obj, float angle);

	bool hit(const Ray& ray, Interval rayT, HitInfo& rec) const override;

	AABB boundingBox()const override;

private:
	std::shared_ptr<HitTable> obj;
	float sinTheta;
	float cosTheta;
	AABB bbox;
};