#include "ImageTexture.h"

Color ImageTexture::value(float u, float v, const Point3& point) const
{
	if (image.height() <= 0) return Color(1.0, 0.0, 0.0);

	u = Interval(0.0, 1.0).clamp(u);
	v = 1.0 - Interval(0.0, 1.0).clamp(v);

	int xIndex = static_cast<int>(u * image.width());
	int yIndex = static_cast<int>(v * image.height());

	auto pixel = image.pixelData(xIndex, yIndex);
	float valueScale = 1.0 / 255.0;
	return Color(valueScale * pixel[0], valueScale * pixel[1], valueScale *pixel[2]);
}
