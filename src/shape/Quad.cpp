#include "Quad.h"

Quad::Quad(Point3 Q, Vec3 u, Vec3 v, std::shared_ptr<Material> mat):
	Q(Q), u(u), v(v), mat(mat){
	auto n = cross(u, v);
	normal = unitVector(n);
	D = dot(normal, Q);
	w = n / dot(n, n);

	setBoundingBox();
}

void Quad::setBoundingBox()
{
	AABB bboxDiagonal1 = AABB(Q, Q + u + v);
	AABB bboxDiagonal2 = AABB(Q + u, Q + v);
	bbox = AABB(bboxDiagonal1, bboxDiagonal2);
}

AABB Quad::boundingBox()const
{
	return bbox;
}

bool Quad::hit(const Ray& ray, Interval rayT, HitInfo& rec) const
{
	float proj = dot(normal, ray.direction());
	if (std::fabs(proj) < 1e-8) 
		return false;
	// note that: Vec3 <ray.direction and ray.origion> is not same(or near)direction
	float t = (D - dot(normal, ray.origion())) / proj;
	//std::cout << "t" << t << std::endl;
	if(!rayT.contains(t)) 
		return false;
	
	Point3 interaction = ray.at(t);
	Vec3 planarHitPtVector = interaction - Q;
	auto alpha = dot(w, cross(planarHitPtVector, v));
	auto beta = dot(w, cross(u, planarHitPtVector));
	
	if (!isInterior(alpha, beta, rec))
		return false;

	rec.t = t;
	rec.p = interaction;
	rec.material = mat;
	rec.setFaceNormal(ray, normal);
	
	return true;
}

bool Quad::isInterior(float a, float b, HitInfo& rec) const
{
	Interval unitInterval{ 0.0, 1.0 };

	// <len(a, b) < r?> or <a > 0 && b > 0 && (a + b) < 1 >
	if (!unitInterval.contains(a) || !unitInterval.contains(b))
		return false;
	//Vec3 uws{ a, b, 0 };
	//if (uws.length() < 0.5) return false;

	//if (a > 0.0 && b > 0.0 && a + b) < 1.0) return false;

	rec.u = a;
	rec.v = b;
	return true;
}

