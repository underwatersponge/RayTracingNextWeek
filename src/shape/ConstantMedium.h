#pragma once
#include "../hit/Hit.hpp"
#include "../mat/MaterialBase.h"
#include "../tex/Texture.h"
#include"../mat/Isotropic.h"

// this maybe not is a shape ? 
class ConstantMedium : public HitTable {
public:
	ConstantMedium(std::shared_ptr<HitTable> boundary, float density, std::shared_ptr<Texture> tex);

	ConstantMedium(std::shared_ptr<HitTable> boundary, float density, const Color& albedo);

	bool hit(const Ray& ray, Interval rayT, HitInfo& rec)const override;

	AABB boundingBox()const override;

private:
	std::shared_ptr<HitTable> boundary;
	float negInvDensity;
	std::shared_ptr<Material> phasefunction;
};