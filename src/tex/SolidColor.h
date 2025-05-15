#pragma once
#include "Texture.h"

class SolidColor : public Texture {
public:
	SolidColor(const Color& albedo) : albedo(albedo) {}
	SolidColor(float r, float g, float b) : SolidColor(Color(r, g, b)){}
	
	Color value(float u, float v, const Point3& point)const override;

private:
	Color albedo;
};