#pragma once
#include "../hit/Hit.hpp"
#include "../ray/Ray.hpp"
#include "bbox/AABB.h"
#include <vector>
#include <memory>

class HitTableList : public HitTable {
public:
	HitTableList() {};
	HitTableList(std::shared_ptr<HitTable> obj) { add(obj); }

	void add(std::shared_ptr<HitTable> obj) {
		objects.push_back(obj);
		bbox = AABB(bbox, obj->boundingBox());
	}

	void clear() { objects.clear(); }

	bool hit(const Ray& ray, Interval t, HitInfo& rec)const override;

	AABB boundingBox()const override { return bbox; }

public:
	std::vector<std::shared_ptr<HitTable>> objects;
private:
	AABB bbox;
};