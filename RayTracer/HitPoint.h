#pragma once
#include "Vec3d.h"
#include "Ray.h"

class Object;
class Color;

class HitPoint
{
public:
	HitPoint(Ray r);
	void setObject(const Object* s);
	bool isHit();
	Color getColor();
	void setHit(Vec3d p);
	Vec3d getNormal() const;
	Vec3d getPoint() const;
	double getShine() const;
	double getSpecular() const;
	double getDiffuse() const;
	double getReflect() const;
	Color getEmission() const;
	Ray getRay() const;

private:
	Ray ray;
	const Object* object;
	Vec3d point;
};

