#pragma once
#include <optional>
#include <memory>
#include <vector>
#include "Vec3d.h"
#include "Sphere.h"
class Ray;
class hitPoint;
class Object;
class BoundingSphere
{
public:
	using Child = std::unique_ptr<BoundingSphere>;
	using Data = Object*;
	BoundingSphere(Child&& l, Child&& r, double rad, Vec3d cen);
	BoundingSphere(Data ob);
	BoundingSphere(BoundingSphere&& rhs) noexcept;
	~BoundingSphere() noexcept = default;
	BoundingSphere& operator=(BoundingSphere&& rhs) noexcept;


	HitPoint intersects(Ray r);
	
	Vec3d getCenter();
	double getRadius();


private:

	Child left;
	Child right;
	Sphere bounding;
	Data data;
};

std::unique_ptr<BoundingSphere> buildBoundingSphere(const std::vector<std::unique_ptr<Object>>& objects);