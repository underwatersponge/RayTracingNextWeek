#include "Sphere.h"

bool Sphere::hit(const Ray& ray, Interval t, HitInfo& rec) const
{
	Point3 currentCenter = center.at(ray.time());
	Vec3 oc = currentCenter - ray.origion();

	//float a = dot(ray.direction(), ray.direction());
	//float b = -2.0 * dot(ray.direction(), oc);
	//float c = dot(oc, oc) - radius * radius;

	// a litter improve in mathmtactill
	float a = ray.direction().lengthSquared();
	float h = dot(ray.direction(), oc);
	float c = oc.lengthSquared() - radius * radius;

	float discriminant = h * h - a * c;
	if (discriminant < 0.0) { return false; }

	float sqrtD = std::sqrt(discriminant);

	// find nearst t in acceptable range
	float root = (h - sqrtD) / a;
	if (!t.surrounds(root)) {
		root = (h + sqrtD) / a;
		if (!t.surrounds(root)) {
			return false;
		}
	}

	rec.t = root;
	rec.p = ray.at(rec.t);
	Vec3 outwardNormal = (rec.p - currentCenter) / radius;
	rec.setFaceNormal(ray, outwardNormal);
	getSphereUV(outwardNormal, rec.u, rec.v);
	rec.material = material;

	return true;
}

void Sphere::getSphereUV(const Point3& p, float& u, float& v) const
{
	float theta = std::acos(-p.y);
	float phi = std::atan2f(-p.z, p.x) + pi;
	
	float value = 1.0 / pi;
	u = phi * 0.5 * value;
	v = theta * value;
}
