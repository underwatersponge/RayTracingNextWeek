#include "Isotropic.h"

Isotropic::Isotropic(const Color& albedo) : tex(std::make_shared<SolidColor>(albedo)) {}

Isotropic::Isotropic(const std::shared_ptr<Texture> tex): tex(tex){}

bool Isotropic::scatter(const Ray& ray, const HitInfo& rec, Color& attenuation, Ray& scattered) const
{
	scattered = Ray(rec.p, randUnitVector(), ray.time());
	attenuation = tex->value(rec.u, rec.v, rec.p);
	return true;
}

