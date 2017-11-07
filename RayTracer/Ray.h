#pragma once
#include "Vec3d.h"

class Ray
{
public:
	Ray(Vec3d s, Vec3d dir):start(s), direction(dir.normalize()){}
	
	
	Vec3d getStart(){return start;}
	Vec3d getDirection(){return direction;}
	
private:
	Vec3d start;
	Vec3d direction;
};

