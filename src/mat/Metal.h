#pragma once
#include "MaterialBase.h"

class Metal : public Material{
public:
	Metal(const Color& albedo, float fuzz) : albedo(albedo), fuzz(fuzz) {}

	bool scatter(const Ray& rayIn, const HitInfo& rec, Color& attenuation, Ray& scattered)const override;

private:
	Color albedo;
	float fuzz;
};