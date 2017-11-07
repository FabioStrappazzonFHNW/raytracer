#include "Vec2d.h"
#include <math.h>
#include <cassert>

constexpr long double pi(){
	return 3.141592653589793238L;
}

Vec2d::Vec2d():
	x(0),
	y(0) {
}

Vec2d::Vec2d(const double xval, const double yval): x(xval), y(yval) {
}

Vec2d::Vec2d(std::initializer_list<double> list) {
	//empty initializer list calls default constructor
	assert(list.size()==2);//, "Wrong number of arguments in initializer_list for Vec2d. 0 and 2 are allowed.");
	auto it = list.begin();
	x = *it;
	y = *++it;
}


Vec2d& Vec2d::operator=(const Vec2d &rhs) {
	if(this==&rhs) {
		return *this;
	}
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Vec2d& Vec2d::operator+=(const Vec2d &rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec2d& Vec2d::operator-=(const Vec2d &rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec2d& Vec2d::operator*=(const double &rhs) {
	x *= rhs;
	y *= rhs;
	return *this;
}

Vec2d& Vec2d::operator/=(const double &rhs) {
	if(rhs) {
		x /= rhs;
		y /= rhs;
	}
	return *this;
}

double Vec2d::operator*=(const Vec2d &rhs) {
	return x*rhs.x+y*rhs.y;
}

Vec2d operator+(Vec2d lhs, const Vec2d& rhs) {
	return lhs+=rhs;
}

Vec2d operator-(Vec2d lhs, const Vec2d& rhs) {
	return lhs-=rhs;
}

Vec2d operator*(Vec2d lhs, const double& rhs) {
	return lhs*=rhs;
}

Vec2d operator/(Vec2d lhs, const double& rhs) {
	return lhs/=rhs;
}

Vec2d operator*(const double lhs, Vec2d rhs) {
	return rhs*=lhs;
}

double operator*(Vec2d lhs, const Vec2d& rhs) {
	return lhs*=rhs;
}

Vec2d Vec2d::normalize() const {
	auto copy = *this;
	copy /= copy.magnitude();
	return copy;
}

double Vec2d::magnitude() const {
	return sqrt(magnitudeSquared());
}

double Vec2d::magnitudeSquared() const {
	return (x*x)+(y*y);
}

double distance(const Vec2d& lhs, const Vec2d& rhs) {
	return (lhs - rhs).magnitude();
}

double distanceSquared(const Vec2d& lhs, const Vec2d& rhs) {
	return (lhs - rhs).magnitudeSquared();
}
