#include "Lambertian.h"

bool Lambertian::scatter(const Ray& rayIn, const HitInfo& rec, Color& attenuation, Ray& scattered) const
{
    auto scatterDirection = rec.normal + randomOnHemisphere(rec.normal);
    scatterDirection = scatterDirection.nearZero() ? rec.normal : scatterDirection;

    scattered = Ray(rec.p, scatterDirection, rayIn.time());
    attenuation = tex->value(rec.u, rec.v, rec.p);
    
    return true;
}
