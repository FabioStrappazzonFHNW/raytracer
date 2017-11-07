#pragma once
#include <vector>
#include "Color.h"

#include "Vec3d.h"
class Ray;
class HitPoint;

class Object
{
public:
	Object(Vec3d ce, double rad, Color co, double sh, double di, double sp, double re, double em);
	virtual ~Object() noexcept = default;
	Object(const Object&) = default;
	Object(Object&&) noexcept = default;
	Object& operator=(const Object&) = default;
	Object& operator=(Object&&) noexcept = default;

	virtual Color getColor(Vec3d point) const;
	double getShine() const;
	double getSpecular() const;
	double getDiffuse() const;
	double getReflect() const;
	virtual Color getEmission() const;

	virtual Vec3d getNormal(HitPoint hp) const = 0;
	virtual std::vector<Vec3d> intersects(Ray r) const = 0;
	Vec3d getCenter() const;
	double getRadius() const;

protected:

	Color color;
	Vec3d center;
	double radius;
	double shine;
	double diffuse;
	double specular;
	double reflect;
	double emission;
};

