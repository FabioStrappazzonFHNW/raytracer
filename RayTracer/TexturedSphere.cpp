#include "TexturedSphere.h"
#include "Surface.h"
#include "Vec3d.h"
#include "HitPoint.h"
#include "Color.h"
using namespace std;


TexturedSphere::TexturedSphere(Vec3d c, double r, const Surface * surf, double shine, double diffuse, double specular, double reflect,  double emission, Color color):
	Sphere(c, r, color, shine, diffuse, specular, reflect, emission),
	surface(surf)
{
}

Color TexturedSphere::getColor(Vec3d pos) const
{
	pos -= center;
	return surface->getColor(pos.normalize()) * color;
}

Color TexturedSphere::getEmission() const
{
	return emission*color;
}

Vec3d TexturedSphere::getNormal(HitPoint hp) const
{
	double insideSphere = 1;
	if (distanceSquared(hp.getRay().getStart(), center) < radius * radius) {
		insideSphere = -1;
	}
	return (hp.getPoint() - center).normalize() * insideSphere;
}