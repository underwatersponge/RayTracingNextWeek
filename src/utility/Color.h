#pragma once
#include "Vec3.hpp"

using Color = Vec3;;

inline float linearToGamma(float linear) {
	if (linear > 0.0) {
		return std::sqrt(linear);
	}
	return 0.0;
}

void writeColor(std::ofstream& out, const Vec3& pixCol);
