#pragma once
#include "MaterialBase.h"
#include "../tex/Texture.h"
#include "../tex/SolidColor.h"

class Isotropic : public Material {
public:
	Isotropic(const Color& albedo);
	Isotropic(const std::shared_ptr<Texture> tex);

	bool scatter(const Ray& ray, const HitInfo& rec, Color& attenuation, Ray& scattered) const override;

private:
	std::shared_ptr<Texture> tex;
};