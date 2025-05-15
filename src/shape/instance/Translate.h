#pragma once
#include"../../hit/Hit.hpp"
#include "../../mat/MaterialBase.h"

class Translate : public HitTable {
public:
	Translate(std::shared_ptr<HitTable> obj, const Vec3& offset);

	bool hit(const Ray& ray, Interval rayT, HitInfo& rec)const override;

	AABB boundingBox()const override;

private:
	std::shared_ptr<HitTable> obj;
	AABB bbox;
	Vec3 offset;
};