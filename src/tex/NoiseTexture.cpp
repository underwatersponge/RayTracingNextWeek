#include "NoiseTexture.h"

Color NoiseTexture::value(float u, float v, const Point3& p) const
{
    //return Color{ 1.0, 1.0, 1.0 } * 0.5  * (1.0 + noise.noise(scale * p));
    //return Color(1.0, 1.0, 1.0) * noise.turb(p, 7);
    return Color(0.5, 0.5, 0.5) * (1.0 + std::sin(scale * p.z + 10 * noise.turb(p, 7)));
}
