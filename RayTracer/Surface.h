#pragma once
#include <vector>

struct SDL_Surface;
class Color;
class Vec3d;

class Surface
{
public:
	Surface(const char* name, int size = 0);
	Surface(const Surface&) = delete;
	Surface& operator=(const Surface&) = delete;
	Surface(Surface&& rhs);
	Surface& operator=(Surface&& rhs);
	~Surface();

	
	Color getColor(Vec3d coords) const;



private:
	void free();

	SDL_Surface* surface;
	std::vector<float> floats;
	bool isBmp;
	int size;
};

