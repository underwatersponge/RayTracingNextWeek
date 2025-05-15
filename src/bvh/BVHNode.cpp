#include "BVHNode.h"

BVHNode::BVHNode(std::vector<std::shared_ptr<HitTable>>& objects, size_t start, size_t end)
{
    bbox = AABB::empty;
    for (size_t objectIndex = start; objectIndex < end; objectIndex++) {
        bbox = AABB(bbox, objects[objectIndex]->boundingBox());
    }
    
    int axis = bbox.longestAxis();

    auto comparator = (axis == 0) ? boxXCompare :
        (axis == 1) ? boxYCompare :
        boxZCompare;

    size_t objectSpan = end - start;
    if (objectSpan == 1) {
        left = right = objects[start];
    }
    else if (objectSpan == 2) {
        left = objects[start];
        right = objects[start + 1];
    }
    else {
        std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator);
        //std::sort(objects.cbegin() + start, objects.cbegin() + end, comparator);
        auto mid = start + objectSpan / 2;
        left = std::make_shared<BVHNode>(objects, start, mid);
        right = std::make_shared<BVHNode>(objects, mid, end);
    }
}

bool BVHNode::hit(const Ray& ray, Interval rayT, HitInfo& rec) const
{
    if (!bbox.hit(ray, rayT)) {
        return false;
    }

    bool hitLeft = left->hit(ray, rayT, rec);
    bool hitRight = right->hit(ray, Interval(rayT.min, hitLeft ? rec.t : rayT.max), rec);

    return hitLeft || hitRight;
}

bool BVHNode::boxCompare(const std::shared_ptr<HitTable> a, const std::shared_ptr<HitTable> b, int axisIndex)
{
    // uws
    auto aAxisInterval = a->boundingBox().axisInterval(axisIndex);
    auto bAxisInterval = b->boundingBox().axisInterval(axisIndex);
    return aAxisInterval.min < bAxisInterval.min;
}


