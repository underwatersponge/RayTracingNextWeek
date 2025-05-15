#pragma once
#include "../hit/Hit.hpp"
#include "../utility/Color.h"

class Material {
public:
	virtual ~Material(){}

	virtual bool scatter(const Ray& rayIn, const HitInfo& hitinfo, Color& attenuation, Ray& scatered)const = 0;

	virtual Color emitted(float u, float v, const Vec3& p)const {
		return Color{ 0.0, 0.0, 0.0 };
	}
};