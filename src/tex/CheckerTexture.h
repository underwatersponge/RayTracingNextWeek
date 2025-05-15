#pragma once
#include "SolidColor.h"
#include <memory>

class CheckTexture : public Texture{
public:
	CheckTexture(float value, std::shared_ptr<Texture>even , std::shared_ptr<Texture> odd);
	CheckTexture(float value, const Color& even, const Color& odd);

	Color value(float u, float v, const Point3& point) const override;

private:
	float scale;
	std::shared_ptr<Texture> even;
	std::shared_ptr<Texture> odd;
};