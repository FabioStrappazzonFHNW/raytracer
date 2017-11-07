#pragma once
#include "Vec3d.h"
#include "Color.h"

class Light
{
public:
	Light(Vec3d pos, Color col);

	Vec3d getPosition() const;
	Color getColor() const;
private:
	Vec3d position;
	Color color;
};

