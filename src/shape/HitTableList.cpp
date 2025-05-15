#include "HitTableList.h"

bool HitTableList::hit(const Ray& ray, Interval t, HitInfo& rec) const
{
    bool hitAnything = false;
    HitInfo tempHitInfo;
    float closedSofar = t.max;

    for (auto& obj : objects) {
        if (obj->hit(ray, Interval(t.min, closedSofar), tempHitInfo)) { 
            //std::cout << "hit something";
            hitAnything = true;
            closedSofar = tempHitInfo.t; 
            rec = tempHitInfo;
        }

    }

    return hitAnything;
}
