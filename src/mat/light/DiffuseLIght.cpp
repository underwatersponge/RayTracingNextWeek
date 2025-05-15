#include "DiffuseLIght.h"

Color DiffuseLight::emitted(float u, float v, const Point3& p) const
{
    return tex->value(u, v, p);
}
