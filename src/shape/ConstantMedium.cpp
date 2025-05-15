#include "ConstantMedium.h"

ConstantMedium::ConstantMedium(std::shared_ptr<HitTable> boundary, float density, std::shared_ptr<Texture> tex):
    boundary(boundary), negInvDensity(1.0 / density), phasefunction(std::make_shared<Isotropic>(tex))
{ }

ConstantMedium::ConstantMedium(std::shared_ptr<HitTable> boundary, float density, const Color& albedo) :
    boundary(boundary), negInvDensity(1.0 / density), phasefunction(std::make_shared<Isotropic>(albedo))
{ }

bool ConstantMedium::hit(const Ray & ray, Interval rayT, HitInfo & rec) const
{
    HitInfo rec1, rec2;

    if (!boundary->hit(ray, Interval::universe, rec1))
        return false;

    if (!boundary->hit(ray, Interval(rec1.t + 0.0001, infinity), rec2))
        return false;

    if (rec1.t < rayT.min) rec1.t = rayT.min;
    if (rec2.t > rayT.max) rec2.t = rayT.max;

    if (rec1.t >= rec2.t)
        return false;
    
    if (rec1.t < 0.0)
        rec1.t = 0.0;

    auto rayLength = ray.direction().length();
    auto distanceInsideBoundary = (rec2.t - rec1.t) * rayLength;
    auto hitDistance = negInvDensity * std::log(randFloat());

    if (hitDistance > distanceInsideBoundary)
        return false;

    rec.t = rec.t + hitDistance / rayLength;
    rec.p = ray.at(rec.t);
    
    rec.normal = Vec3(1.0, 0.0, 0.0);
    rec.frontFace = true;
    rec.material = phasefunction;

    return true;
}


AABB ConstantMedium::boundingBox() const
{
    return boundary->boundingBox();
}
