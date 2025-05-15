#include "Metal.h"

bool Metal::scatter(const Ray& rayIn, const HitInfo& rec, Color& attenuation, Ray& scattered) const
{
    Vec3 reflected = reflect(rayIn.direction(), rec.normal);
    reflected += fuzz * randUnitVector();
    reflected = unitVector(reflected);
    scattered = Ray(rec.p, reflected, rayIn.time());
    attenuation = albedo;

    return (dot(scattered.direction(), rec.normal) > 0.0);
}
