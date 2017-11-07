#pragma once
#include "Sphere.h"
class Surface;
class Vec3d;
class Color;

class TexturedSphere :
	public Sphere
{
public:
	TexturedSphere(Vec3d c, double r, const Surface* surf , double shine, double diffuse, double specular, double reflect, double emission, Color color = Color(1.0, 1.0, 1.0));
	virtual ~TexturedSphere() noexcept override = default;
	TexturedSphere(const TexturedSphere&) = default;
	TexturedSphere(TexturedSphere&&) noexcept = default;
	TexturedSphere& operator=(const TexturedSphere&) = default;
	TexturedSphere& operator=(TexturedSphere&&) noexcept = default;

	virtual Color getColor(Vec3d pos) const override;
	virtual Vec3d getNormal(HitPoint hp) const override;
	virtual Color getEmission() const override;

private:
	const Surface* surface;
};

