#include "Vec3d.h"
#include <math.h>
#include <cassert>

constexpr long double pi(){
	return 3.141592653589793238L;
}

Vec3d::Vec3d():
	x(0),
	y(0),
	z(0){
}

Vec3d::Vec3d(const double xval, const double yval, const double zval): x(xval), y(yval), z(zval) {
}

Vec3d::Vec3d(std::initializer_list<double> list) {
	//empty initializer list calls default constructor
	assert(list.size()==3);//, "Wrong number of arguments in initializer_list for Vec3d. 0 and 3 are allowed.");
	auto it = list.begin();
	x = *it;
	y = *++it;
	z = *++it;
}


Vec3d& Vec3d::operator=(const Vec3d &rhs) {
	if(this==&rhs) {
		return *this;
	}
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

Vec3d& Vec3d::operator+=(const Vec3d &rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vec3d& Vec3d::operator-=(const Vec3d &rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vec3d& Vec3d::operator*=(const double &rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

Vec3d& Vec3d::operator/=(const double &rhs) {
	if(rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
	}
	return *this;
}

double Vec3d::operator*=(const Vec3d &rhs) {
	return x*rhs.x + y*rhs.y + z*rhs.z;
}

Vec3d operator+(Vec3d lhs, const Vec3d& rhs) {
	return lhs+=rhs;
}

Vec3d operator-(Vec3d lhs, const Vec3d& rhs) {
	return lhs-=rhs;
}

Vec3d operator*(Vec3d lhs, const double& rhs) {
	return lhs*=rhs;
}

Vec3d operator/(Vec3d lhs, const double& rhs) {
	return lhs/=rhs;
}

Vec3d operator*(const double lhs, Vec3d rhs) {
	return rhs*=lhs;
}

double operator*(Vec3d lhs, const Vec3d& rhs) {
	return lhs*=rhs;
}

Vec3d Vec3d::normalize() const{
	auto copy = *this;
	copy /= copy.magnitude();
	return copy;
}

double Vec3d::magnitude() const {
	return sqrt(magnitudeSquared());
}

double Vec3d::magnitudeSquared() const {
	return (x*x)+(y*y)+(z*z);
}

double distance(const Vec3d& lhs, const Vec3d& rhs) {
	return (lhs - rhs).magnitude();
}

double distanceSquared(const Vec3d& lhs, const Vec3d& rhs) {
	return (lhs - rhs).magnitudeSquared();
}



Vec3d cross(const Vec3d& lhs, const Vec3d& rhs){
	return {
		lhs.y *  rhs.z - lhs.z * rhs.y,
		lhs.z *  rhs.x - lhs.x * rhs.z,
		lhs.x *  rhs.y - lhs.y * rhs.x
		};
}