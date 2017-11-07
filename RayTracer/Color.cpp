#include "Color.h"
#include <algorithm>
using namespace std;

Color::Color():red(0.0),green(0.0),blue(0.0)
{
}

Color::Color(double r, double g, double b):red(r),green(g),blue(b)
{
	
}

Color::Color(uint8_t r, uint8_t g, uint8_t b):Color(r/255.0, g/255.0, b/255.0)
{
}

Color::Color(uint32_t color):Color(static_cast<uint8_t>(color>>16), static_cast<uint8_t>((color >> 8) & 0xff), static_cast<uint8_t>(color & 0xff))
{
}


uint32_t gammaEncode(double x) {
	const double gamma = 2.2;
	return static_cast<uint32_t>(pow(clamp(x, 0.0, 1.0) , 1/gamma)*255);
}

Color::operator uint32_t() const
{
	return gammaEncode(red) << 16 | gammaEncode(green) << 8 | gammaEncode(blue);
}

Color & Color::operator+=(const Color & rhs)
{
	red += rhs.red;
	green += rhs.green;
	blue += rhs.blue;
	return *this;
}

Color& Color::operator*=(const double& rhs)
{
	red *= rhs;
	green *= rhs;
	blue *= rhs;

	return *this;
}


Color& Color::operator-=(const Color &rhs) {
	red -= rhs.red;
	green -=  rhs.green;
	blue -= rhs.blue;
	return *this;
}


Color& Color::operator/=(const double &rhs) {
	if (rhs) {
		red /= rhs;
		green /= rhs;
		blue /= rhs;
	}
	return *this;
}

Color& Color::operator*=(const Color & rhs)
{
	red *= rhs.red;
	green *= rhs.green;
	blue *= rhs.blue;
	return *this;
}

Color operator+(Color lhs, const Color& rhs) {
	return lhs += rhs;
}

Color operator-(Color lhs, const Color& rhs) {
	return lhs -= rhs;
}

Color operator*(Color lhs, const double& rhs) {
	return lhs *= rhs;
}

Color operator/(Color lhs, const double& rhs) {
	return lhs /= rhs;
}

Color operator*(const double lhs, Color rhs) {
	return rhs *= lhs;
}

Color operator*(Color lhs, const Color & rhs)
{
	return lhs *= rhs;;
}


