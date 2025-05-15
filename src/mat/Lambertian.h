#pragma once
#include "MaterialBase.h"
#include "../tex/Texture.h"
#include"../tex/SolidColor.h"

class Lambertian : public Material{
public:
	Lambertian(const Color& albedo): tex(std::make_shared<SolidColor>(albedo)){}
	Lambertian(const std::shared_ptr<Texture> tex) : tex(tex) {}

	bool scatter(const Ray& rayIn, const HitInfo& rec, Color& attenuation, Ray& scattered)const override;

private:
	std::shared_ptr<Texture> tex;
};