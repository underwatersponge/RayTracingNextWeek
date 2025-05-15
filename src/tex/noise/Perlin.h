#pragma once
#include <vector>
#include "../../utility/Utility.hpp"
#include "../../utility/Vec3.hpp"

class Perlin {
public:
	Perlin();

	float noise(const Point3& p)const;
	float turb(const Point3& p, int depth)const;

private:
	static const int pointCount = 256;
	std::vector<Vec3> randVec;
	std::vector<int> permX;
	std::vector<int> permY;
	std::vector<int> permZ;

private:
	static void perlinGeneratePerm(std::vector<int>& p);

	static void permute(std::vector<int>& p, int n);

	//static float trilinearInterp(float c[2][2][2], float u, float v, float w);
	static float perlinInterp(Vec3 c[2][2][2], float u, float v, float w);
};