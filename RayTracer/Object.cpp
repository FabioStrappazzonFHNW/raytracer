#include "Object.h"
#include "Vec3d.h"



Object::Object(Vec3d ce, double rad, Color co, double sh, double di, double sp, double re, double em) :
	center(ce),
	radius(rad),
	color(co),
	shine(sh),
	diffuse(di),
	specular(sp),
	reflect(re),
	emission(em){}

Color Object::getColor(Vec3d point) const
{
	return color;
}


double Object::getShine() const
{
	return shine;
}

double Object::getSpecular() const
{
	return specular;
}

double Object::getDiffuse() const
{
	return diffuse;
}

double Object::getReflect() const
{
	return reflect;
}

Color Object::getEmission() const
{
	return emission * color;
}

Vec3d Object::getCenter() const
{
	return center;
}

double Object::getRadius() const
{
	return radius;
}
