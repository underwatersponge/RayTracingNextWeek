#pragma once
#include "../utility/Vec3.hpp"
#include "../utility/Color.h"

class Texture {
public:
	virtual ~Texture() = default;

	virtual Color value(float u, float v, const Point3& point) const = 0;
};