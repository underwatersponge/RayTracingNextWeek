#include "Perlin.h"

Perlin::Perlin()
{
	for (int i = 0; i < pointCount; i++) {
		randVec.push_back(unitVector(Vec3::random(-1, 1)));
	}

	perlinGeneratePerm(permX);
	perlinGeneratePerm(permY);
	perlinGeneratePerm(permZ);
}

float Perlin::noise(const Point3& p) const
{
	auto u = p.x - std::floor(p.x);
	auto v = p.y - std::floor(p.y);
	auto w = p.z - std::floor(p.z);
	//u = u * u * (3.0 - 2.0 * u);
	//v = v * v * (3.0 - 2.0 * v);
	//w = w * w * (3.0 - 2.0 * w);

	auto i = static_cast<int>(std::floor(p.x));
	auto j = static_cast<int>(std::floor(p.y));
	auto k = static_cast<int>(std::floor(p.z));
	Vec3 c[2][2][2];
	// 
	//https://www.cnblogs.com/yingying0907/archive/2012/11/21/2780092.html
	for (int di = 0; di < 2; di++) {
		for (int dj = 0; dj < 2; dj++) {
			for (int dk = 0; dk < 2; dk++) {
				c[di][dj][dk] = randVec[
						permX[(i + di) & 255] ^
						permY[(j + dj) & 255] ^
						permZ[(k + dk) & 255]
				];
			}
		}
	}
	return perlinInterp(c, u, v, w);
	//return trilinearInterp(c, u, v, w);

}

float Perlin::turb(const Point3& p, int depth) const
{
	auto accum = 0.0;
	auto tempP = p;
	auto weight = 1.0;

	for (int i = 0; i < depth; i++) {
		accum += weight * noise(tempP);
		weight *= 0.5;
		tempP *= 2.0;
	}
	return std::fabs(accum);
}

void Perlin::perlinGeneratePerm(std::vector<int>& p)
{
	for (int i = 0; i < pointCount; i++) {
		p.push_back(i);
	}
	
	permute(p, pointCount);
}

void Perlin::permute(std::vector<int>& p, int n)
{
	for (int i = n - 1; i > 0; i--) {
		int target = randInt(0, i);
		int temp = p[i];//p.at(i);
		p[i] = p[target];
		p[target] = temp;
	}
}

float Perlin::perlinInterp(Vec3 c[2][2][2], float u, float v, float w)
{
	auto uu = u * u * (3 - 2 * u);
	auto vv = v * v * (3 - 2 * v);
	auto ww = w * w * (3 - 2 * w);
	auto accum = 0.0;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++) {
				Vec3 weightV(u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu))
					* (j * vv + (1 - j) * (1 - vv))
					* (k * ww + (1 - k) * (1 - ww))
					* dot(c[i][j][k], weightV);
			}

	return accum;
}

//float Perlin::trilinearInterp(float c[2][2][2], float u, float v, float w)
//{
//	//https://www.cnblogs.com/yingying0907/archive/2012/11/21/2780092.html
//	auto accum = 0.f;
//	for (int i = 0; i < 2; i++) {
//		for (int j = 0; j < 2; j++) {
//			for (int k = 0; k < 2; k++) {
//				accum += (i * u + (1 - i) * (1 - u))
//					* (j * v + (1 - j) * (1 - v))
//					* (k * w + (1 - k) * (1 - w))
//					* c[i][j][k];
//			}
//		}
//	}
//	return accum;
//}
