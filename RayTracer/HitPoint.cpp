#include "HitPoint.h"
#include "Object.h"


HitPoint::HitPoint(Ray r): ray(r), object(nullptr)
{
}

void HitPoint::setObject(const Object * o)
{
	object = o;
}

bool HitPoint::isHit()
{
	return object != nullptr;
}

Color HitPoint::getColor()
{
	return object->getColor(point);
}

void HitPoint::setHit(Vec3d p)
{
	point = p;
}

Vec3d HitPoint::getNormal() const
{
	return object->getNormal(*this);
}

Vec3d HitPoint::getPoint() const
{
	return point;
}

double HitPoint::getShine() const
{
	return object->getShine();
}

double HitPoint::getSpecular() const
{
	return object->getSpecular();
}

double HitPoint::getDiffuse() const
{
	return object->getDiffuse();
}

double HitPoint::getReflect() const
{
	return object->getReflect();
}

Color HitPoint::getEmission() const
{
	return object->getEmission();
}

Ray HitPoint::getRay() const
{
	return ray;
}
