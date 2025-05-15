#pragma once
#include "../utility/Vec3.hpp"
#include "../utility/Color.h"
#include "../ray/Ray.hpp"
#include "../shape/HitTableList.h"
#include <fstream>
#include <filesystem>
#include "../utility/Interval.h"

class Camera {

public:
	void render(std::ofstream& out, const HitTableList& scene);

private:
	void initialized();
	std::pair<float, float> sampleSquare();
	Ray getRay(int vertical, int horizontal);
	Color rayColor(const Ray& ray, int depth, const HitTableList& scene)const;
	Point3 defocusDiskSample()const;

public:
	float aspectRatio = 1.0;
	int imageWidth = 100;
	size_t samplesPerPixel = 10;
	int maxDepth = 2;
	float fov = 90.0;
	Color background;

	Vec3 lookFrom{ 0.0, 0.0, 0.0 };
	Vec3 lookAt{ 0.0, 0.0, -1.0 };
	Vec3 vup{ 0.0, 1.0, 0.0 };

	float defocusAngle = 0.0;
	float focusDist = 10.0;

private:
	Point3 center;
	float imageHeight;
	Point3 pixelUperLeft;
	Vec3 pixelDeltaU;
	Vec3 pixelDeltaV;
	float pixelSampleScale;

	Vec3 u, v, w;

	Vec3 defocusDiskU;
	Vec3 defocusDiskV;
};