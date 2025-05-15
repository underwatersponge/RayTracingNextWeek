#include "CheckerTexture.h"

CheckTexture::CheckTexture(float value, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd) :
	scale(1.0 / value),
	even(even),
	odd(odd) {}

CheckTexture::CheckTexture(float value, const Color& even, const Color& odd) :
	CheckTexture(value, std::make_shared<SolidColor>(even), std::make_shared<SolidColor>(odd)) {}


Color CheckTexture::value(float u, float v, const Point3& point) const
{
	int xIndex = static_cast<int>(std::floor(scale * point.x));
	int yIndex = static_cast<int>(std::floor(scale * point.y));
	int zIndex = static_cast<int>(std::floor(scale * point.z));

	int index = static_cast<int>((xIndex + yIndex + zIndex) % 2);

	return index ? even->value(u, v, point) : odd->value(u, v, point);
}

