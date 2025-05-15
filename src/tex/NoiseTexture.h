#pragma once
#include "TExture.h"
#include"noise/Perlin.h"
#include"load/RTWImage.h"


#include <iostream>

class NoiseTexture : public Texture {
public:
	NoiseTexture(float scale): scale(scale){}

	Color value(float u, float v, const Point3& p) const override;

private:
	Perlin noise;
	float scale;
};