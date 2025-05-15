#pragma once
#include "../hit/Hit.hpp"
#include "../shape/bbox/AABB.h"
#include "../shape/HitTableList.h"
#include <memory>
#include <algorithm>

class BVHNode : public HitTable{
public:
	BVHNode(HitTableList list): BVHNode(list.objects, 0, list.objects.size()){}

	BVHNode(std::vector<std::shared_ptr<HitTable>>& objects, size_t start, size_t end);

	bool hit(const Ray& ray, Interval rayT, HitInfo& rec)const override;

	AABB boundingBox()const override { return bbox; }

private:
	static bool boxCompare(const std::shared_ptr<HitTable> a, const std::shared_ptr<HitTable> b, int axisIndex);
	static bool boxXCompare(const std::shared_ptr<HitTable> a, const std::shared_ptr<HitTable> b) {
		return boxCompare(a, b, 0);
	}
	static bool boxYCompare(const std::shared_ptr<HitTable> a, const std::shared_ptr<HitTable> b) {
		return boxCompare(a, b, 1);
	}
	static bool boxZCompare(const std::shared_ptr<HitTable> a, const std::shared_ptr<HitTable> b) {
		return boxCompare(a, b, 2);
	}

private:
	std::shared_ptr<HitTable> left;
	std::shared_ptr<HitTable> right;
	AABB bbox;
};