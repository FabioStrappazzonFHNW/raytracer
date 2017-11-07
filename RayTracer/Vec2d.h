#pragma once
#include <initializer_list>

class Vec2d
{
public:
	double x;
	double y;

	Vec2d();
	Vec2d(double xval, double yval);
	Vec2d(std::initializer_list<double> list);

	Vec2d& operator=(const Vec2d &rhs);
	Vec2d& operator+=(const Vec2d &rhs);
	Vec2d& operator-=(const Vec2d &rhs);
	Vec2d& operator*=(const double &rhs);
	Vec2d& operator/=(const double &rhs);
	double operator*=(const Vec2d &rhs);


	Vec2d normalize() const;
	double magnitude() const;
	double magnitudeSquared() const;

};

Vec2d operator+(Vec2d lhs, const Vec2d& rhs);
Vec2d operator-(Vec2d lhs, const Vec2d& rhs);
Vec2d operator*(Vec2d lhs, const double& rhs);
Vec2d operator/(Vec2d lhs, const double& rhs);
Vec2d operator*(const double lhs, Vec2d rhs);

double operator*(Vec2d lhs, const Vec2d& rhs);
double distance(const Vec2d& lhs, const Vec2d& rhs);
double distanceSquared(const Vec2d& lhs, const Vec2d& rhs);
