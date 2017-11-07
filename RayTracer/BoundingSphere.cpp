#include "BoundingSphere.h"
#include "Ray.h"
#include "Object.h"
#include "HitPoint.h"
#include <deque>
#include <cassert>
#include <algorithm>
using namespace std;

BoundingSphere::BoundingSphere(Child&& l, Child&& r, double rad, Vec3d cen):
	left(move(l)),
	right(move(r)), 
	bounding(cen, rad, Color(), 0, 0, 0, 0, 0),
	data(nullptr)
{
}

BoundingSphere::BoundingSphere(Data  ob): 
	left(nullptr), 
	right(nullptr),
	bounding(ob->getCenter(), ob->getRadius(), Color(), 0, 0, 0, 0, 0), 
	data(move(ob))
{
}

BoundingSphere::BoundingSphere(BoundingSphere && rhs) noexcept: 
left(move(rhs.left)),
right(move(rhs.right)),
bounding(rhs.bounding),
data(rhs.data)
{
}

BoundingSphere & BoundingSphere::operator=(BoundingSphere && rhs) noexcept
{
	if (this != &rhs) {
		left = move(rhs.left);
		right = move(rhs.right);
		bounding = rhs.bounding;
		data = rhs.data;
	}
	return *this;
}

HitPoint BoundingSphere::intersects(Ray r)
{
	if (data) {
		HitPoint hitpoint(r);
		double closestDistance = std::numeric_limits<double>::infinity();
		auto hits = data->intersects(r);
		for (auto&& hit : hits) {
			auto dist = distance(hit, r.getStart());
			if (dist > 0 && dist<closestDistance) {
				hitpoint.setObject(data);
				hitpoint.setHit(hit);
				closestDistance = dist;
			}
		}
		return hitpoint;
	}
	auto hits = bounding.intersects(r);
	if (hits.empty()) {
		return HitPoint(r);
	}
	auto leftHit = left->intersects(r);
	auto rightHit = right->intersects(r);
	if (!leftHit.isHit()) {
		return rightHit;
	}
	if (!rightHit.isHit()) {
		return leftHit;
	}
	if (distanceSquared(leftHit.getPoint(), r.getStart()) > 
		distanceSquared(rightHit.getPoint(), r.getStart())) {
		return rightHit;
	}
	return leftHit;
}

Vec3d BoundingSphere::getCenter()
{
	return bounding.getCenter();
}

double BoundingSphere::getRadius()
{
	return bounding.getRadius();
}

unique_ptr<BoundingSphere> buildBoundingSphere(const std::vector<std::unique_ptr<Object>>& objects)
{
	vector<unique_ptr<BoundingSphere>> queue;
	for (auto&& o : objects) {
		queue.push_back(make_unique<BoundingSphere>(o.get()));
	}
	while (queue.size() > 1) {
		
		double minDistance = std::numeric_limits<double>::infinity();
		auto second = queue.begin();
		auto first = queue.end();
		for (auto it1 = queue.begin(); it1 < queue.end(); it1++) {
			for (auto it2 = queue.begin(); it2 < queue.end(); it2++) {
				if (it1 != it2) {
					auto dist = distance((*it1)->getCenter(), (*it2)->getCenter());
					if (dist < minDistance) {
						minDistance = dist;
						second = it2;
						first = it1;
					}
				}
			}
		}
		Vec3d center;
		double radius;
		auto dist = distance((*second)->getCenter(), (*first)->getCenter());
		if ((*second)->getRadius() > dist + (*first)->getRadius()) {//first inside second
			center = (*second)->getCenter();
			radius = (*second)->getRadius();
		}
		else if ((*first)->getRadius() > dist + (*second)->getRadius()) {//second inside first
			center = (*first)->getCenter();
			radius = (*first)->getRadius();
		}
		else {
			radius = (dist + (*first)->getRadius() + (*second)->getRadius()) / 2;
			auto toSecond = ((*second)->getCenter() - (*first)->getCenter()).normalize();
			center = (*first)->getCenter() + (toSecond* abs(radius - (*first)->getRadius()));
		}
		auto bs = make_unique<BoundingSphere>(move(*first), move(*second), radius, center);
		queue.erase(remove(queue.begin(), queue.end(), nullptr), queue.end());
		queue.push_back(move(bs));
	}
	return move(queue[0]);
	
}
