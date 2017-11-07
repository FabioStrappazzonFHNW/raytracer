#pragma once
#include "Vec3d.h"
#include "Color.h"
#include "Object.h"

class Ray;


class Sphere : public Object
{
public:
	Sphere(Vec3d c, double r, Color color, double shine, double diffuse, double specular, double reflect, double emission);
	virtual ~Sphere() noexcept override = default;
	Sphere(const Sphere&) = default;
	Sphere(Sphere&&) noexcept = default;
	Sphere& operator=(const Sphere&) = default;
	Sphere& operator=(Sphere&&) noexcept = default;


	std::vector<Vec3d> intersects(Ray r) const override;
	Vec3d getNormal(HitPoint hp) const override;



protected:
};

