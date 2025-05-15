#include "Color.h"
#include "Interval.h"
#include <fstream>

void writeColor(std::ofstream& out, const Vec3& pixCol)
{
	float r = pixCol.x;
	float g = pixCol.y;
	float b = pixCol.z;

	r = linearToGamma(r);
	g = linearToGamma(g);
	b = linearToGamma(b);

	static const Interval intensity{ 0.0, 0.9999999 };
	
	int ri = static_cast<int>(intensity.clamp(r) * 255.999);
	int gi = static_cast<int>(intensity.clamp(g)* 255.999);
	int bi = static_cast<int>(intensity.clamp(b) * 255.999);

	//out << ri << 
	out << ri << ' ' << gi << ' ' << bi << '\n';

}
