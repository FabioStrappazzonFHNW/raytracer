#include "Plane.h"
#include "Ray.h"
#include "HitPoint.h"

Plane::Plane(Vec3d pos, Vec3d norm, double r, Color color, double shine, double diffuse, double specular, double reflect, double emission)
	: Object(pos, r, color, shine, diffuse, specular, reflect, emission),
	normal(norm.normalize())
{
}

std::vector<Vec3d> Plane::intersects(Ray r) const
{
	std::vector<Vec3d> res;
	if (r.getDirection() * normal != 0) {
		auto distance = ((center - r.getStart())*normal) / (r.getDirection() * normal);
		if(distance > 0) {
			auto point = r.getStart() + (r.getDirection()*distance);
			if (distanceSquared(point, center) < radius * radius) {
				res.push_back(point);
			}
		}
	}
	return res;
}

Vec3d Plane::getNormal(HitPoint hp) const
{
	if (hp.getRay().getDirection() * normal < 0) {
		return normal;
	}
	else {
		return -1 * normal; 
	}
}
