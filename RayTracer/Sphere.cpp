#include "Sphere.h"
#include "Ray.h"
#include <cmath>
#include "HitPoint.h"


Sphere::Sphere(Vec3d c, double r, Color color, double shine, double diffuse, double specular, double reflect, double emission) 
	:Object(c, r, color, shine, diffuse, specular, reflect, emission)
{};


std::vector<Vec3d> Sphere::intersects(Ray r) const {
	std::vector<Vec3d> res;
	auto underSqrt = std::pow((r.getDirection() * (r.getStart() - center)), 2) - distanceSquared(r.getStart(), center) + radius*radius;
	if(underSqrt>=0){
		auto sqrt = std::sqrt(underSqrt);
		auto beforeSqrt = -1 * (r.getDirection()*(r.getStart() - center));
		if (beforeSqrt + sqrt > 0) {
			res.push_back(r.getStart() + r.getDirection()*(beforeSqrt + sqrt));
		}
		if(underSqrt > 0 && beforeSqrt - sqrt > 0){
			res.push_back(r.getStart()+r.getDirection()*(beforeSqrt-sqrt));
		}
	}
	return res;
}


Vec3d Sphere::getNormal(HitPoint hp) const
{
	return (hp.getPoint() - center).normalize();
}

