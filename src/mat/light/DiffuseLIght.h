#pragma once
#include "../MaterialBase.h"
#include "../../tex/Texture.h"
#include "../../tex/SolidColor.h"

class DiffuseLight : public Material {
public:
	DiffuseLight(std::shared_ptr<Texture> tex): tex(tex) {}
	DiffuseLight(const Color& emit) : tex(std::make_shared<SolidColor>(emit)) {}

	bool scatter(const Ray& rayIn, const HitInfo& rec, Color& attenuaion, Ray& scattered)const override {
		return false;
	}
	Color emitted(float u, float v, const Point3& p) const override;

private:
	std::shared_ptr<Texture> tex;
};