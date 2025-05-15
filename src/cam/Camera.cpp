#include "Camera.h"
#include "../mat/MaterialBase.h"

Color Camera::rayColor(const Ray& ray, int depth, const HitTableList& scene) const
{
	if (depth <= 0) {
		return Color(0.0, 0.0, 0.0);
	}
	HitInfo rec;

	if (!scene.hit(ray, Interval(0.0001, infinity), rec))
		return background;
	Ray scattered;
	Color attenuation{ 0.0, 0.0, 0.0 };
	Color colorFromEmitted = rec.material->emitted(rec.u, rec.v, rec.p);

	if (!rec.material->scatter(ray, rec, attenuation, scattered))
		return colorFromEmitted;

	Color colorFromScatter = attenuation * rayColor(scattered, depth - 1, scene);
	return colorFromEmitted + colorFromScatter;

	//Vec3 unitDir = unitVector(ray.direction());
	//float ratio = 0.5 * (unitDir.get_y() + 1.0);// <-1, 1> -> <0, 1> now viewportHeight set to 2.0
	//return (1.0 - ratio) * Color(1.0, 1.0, 1.0) + ratio * Color(0.5, 0.7, 1.0);
	
}

void Camera::render(std::ofstream& out, const HitTableList& scene)
{
	initialized();

	out << "P3\n" << imageWidth << ' ' << imageHeight << ' ' << "\n255\n";

	for (int i = 0; i < imageHeight; ++i) {
		std::cout << "\rScanlines remaining: " << (imageHeight - i) << '\n';
		for (int j = 0; j < imageWidth; ++j) {
			Color result{ 0.0, 0.0, 0.0 };
			for (size_t sample = 0; sample < samplesPerPixel; ++sample) {
				auto ray = getRay(i, j);
				result += rayColor(ray, maxDepth, scene);
			}

			writeColor(out, result * pixelSampleScale);

		}
	}

}

Point3 Camera::defocusDiskSample() const
{
	auto p = randOnDisk();
	return center + defocusDiskU * p.x + defocusDiskV * p.y;
}

void Camera::initialized()
{
	center = lookFrom;
	pixelSampleScale = 1.0 / samplesPerPixel;
	imageHeight = static_cast<int>(imageWidth/ aspectRatio);
	imageHeight < 0 ? 1 : imageHeight;

	// every pixel has a virtaul pos in virtual viewport in 3D world
	//float focalLength = (lookAt - lookFrom).length();
	float theta = degreeToRadians(fov);
	float tanTheta = std::tanf(theta / 2.0);
	float viewportHeight = 2.0 * focusDist * tanTheta;
	float viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / imageHeight);

	w = unitVector(lookFrom - lookAt);
	u = unitVector(cross(vup, w));
	v = unitVector(cross(w, u));

	Vec3 viewportU{ viewportWidth * u };
	Vec3 viewportV{ -viewportHeight * v };
	pixelDeltaU = viewportU / imageWidth;
	pixelDeltaV = viewportV / imageHeight;

	Point3 viewportUperLeft = center - (focusDist * w) - 0.5 * viewportU - 0.5 * viewportV;
	pixelUperLeft = viewportUperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

	// Camera defocus disk 
	auto defocusRadius = focusDist * std::tan(degreeToRadians(defocusAngle / 2.0));
	defocusDiskU = u * defocusRadius;
	defocusDiskV = v * defocusRadius;

}

std::pair<float, float> Camera::sampleSquare()
{
	float x = randFloat() - 0.5;
	float y = randFloat() - 0.5;
	return std::make_pair(x, y);
}

Ray Camera::getRay(int vertical, int horizontal)
{
	auto offset = sampleSquare();
	Point3 pixelPos = pixelUperLeft + (pixelDeltaU * (horizontal + offset.first)) + pixelDeltaV * ((vertical + offset.second));
	Vec3 rayPos = (defocusAngle <= 0.0) ? center : defocusDiskSample();
	Vec3 dir = pixelPos - rayPos;
	auto rayTime = randFloat();
	//dir = unitVector(dir);
	return Ray{ rayPos, dir, rayTime };
}

