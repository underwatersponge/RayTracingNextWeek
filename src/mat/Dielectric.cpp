#include "Dielectric.h"

bool Dielectric::scatter(const Ray& ray, const HitInfo& rec, Color& attenuation, Ray& scattered) const
{
	float ri = rec.frontFace ? (1.0 / refractionIndex) : refractionIndex;

	Vec3 dir = unitVector(ray.direction());
	float cosTheta = std::fmin(dot(-dir, rec.normal), 1.0);
	float sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

	bool canRefracted = ri * sinTheta > 1.0;

	Vec3 direction;
	if (canRefracted || reflectance(cosTheta, ri) > randFloat())
		direction = refract(dir, rec.normal, ri);
	else
		direction = reflect(dir, rec.normal);

	attenuation = Color(1.0, 1.0, 1.0);
	scattered = Ray(rec.p, direction, ray.time());
	return true;
}

float Dielectric::reflectance(float cosine, float refractionIndex)
{
	// Schlick approximation for reflectance
	auto r0 = (1.0 - refractionIndex) / (1.0 + refractionIndex);
	r0 = r0 * r0;
	return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5);
}
