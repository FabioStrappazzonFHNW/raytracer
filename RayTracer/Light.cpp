#include "Light.h"

Light::Light(Vec3d pos, Color col):position(pos), color(col)
{
}

Vec3d Light::getPosition() const
{
	return position;
}

Color Light::getColor() const
{
	return color;
}


