#pragma once
#include <cstdint>

class Color
{
public:
	Color();
	Color(double r, double g, double b);
	Color(uint8_t r, uint8_t g, uint8_t b);
	Color(uint32_t);
	operator uint32_t () const;

	Color& operator+=(const Color& rhs);
	Color& operator*=(const double& rhs);
	Color& operator-=(const Color& rhs);
	Color& operator/=(const double& rhs);
	Color& operator*=(const Color& rhs);
	
private:
	double red, green, blue;

};


Color operator+(Color lhs, const Color& rhs);
Color operator-(Color lhs, const Color& rhs);
Color operator*(Color lhs, const double& rhs);
Color operator/(Color lhs, const double& rhs);
Color operator*(const double lhs, Color rhs);
Color operator*(Color lhs, const Color& rhs);