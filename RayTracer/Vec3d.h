#pragma once
#include <initializer_list>

class Vec3d
{
public:
	double x;
	double y;
	double z;

	Vec3d();
	Vec3d(double xval, double yval, double zval);
	Vec3d(std::initializer_list<double> list);
	Vec3d(const Vec3d&) = default;
	Vec3d(Vec3d&&) noexcept = default;
	Vec3d& operator=(Vec3d&&) noexcept = default;

	Vec3d& operator=(const Vec3d &rhs);
	Vec3d& operator+=(const Vec3d &rhs);
	Vec3d& operator-=(const Vec3d &rhs);
	Vec3d& operator*=(const double &rhs);
	Vec3d& operator/=(const double &rhs);
	double operator*=(const Vec3d &rhs);


	Vec3d normalize() const;
	double magnitude() const;
	double magnitudeSquared() const;

};

Vec3d operator+(Vec3d lhs, const Vec3d& rhs);
Vec3d operator-(Vec3d lhs, const Vec3d& rhs);
Vec3d operator*(Vec3d lhs, const double& rhs);
Vec3d operator/(Vec3d lhs, const double& rhs);
Vec3d operator*(const double lhs, Vec3d rhs);

double operator*(Vec3d lhs, const Vec3d& rhs);
double distance(const Vec3d& lhs, const Vec3d& rhs);
double distanceSquared(const Vec3d& lhs, const Vec3d& rhs);

Vec3d cross(const Vec3d& lhs, const Vec3d& rhs);
