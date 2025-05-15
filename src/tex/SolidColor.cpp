#include "SolidColor.h"

Color SolidColor::value(float u, float v, const Point3& point) const
{
    return albedo;
}
