#pragma once
#include "Object.h"
#include "Vec3d.h"

class Plane : public Object
{
public:
	Plane(Vec3d pos, Vec3d norm, double r, Color color, double shine, double diffuse, double specular, double reflect, double emission);
	virtual ~Plane() noexcept override = default;
	Plane(const Plane&) = default;
	Plane(Plane&&) noexcept = default;
	Plane& operator=(const Plane&) = default;
	Plane& operator=(Plane&&) noexcept = default;


	std::vector<Vec3d> intersects(Ray r) const override;
	Vec3d getNormal(HitPoint hp) const override;

private:
	Vec3d normal;
};

