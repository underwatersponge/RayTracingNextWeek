#pragma once
#include "MaterialBase.h"

class Dielectric : public Material {
public:
	Dielectric(float refractionIndex) : refractionIndex(refractionIndex) {}

	bool scatter(const Ray& ray, const HitInfo& rec, Color& attenuation, Ray& scattered)const override;

	static float reflectance(float cosine, float refractionIndex);

private:
	float refractionIndex;
};