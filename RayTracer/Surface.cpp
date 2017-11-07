#include "Surface.h"
#include "SDL.h"
#include "Color.h"
#include "Vec2d.h"
#include "Vec3d.h"
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
constexpr long double pi() {
	return 3.141592653589793238L;
}

Surface::Surface(const char * name, int si): surface(nullptr), floats(si*si*3, 0), isBmp(false), size(si)
{
	string s = name;
	if (s.find(".float") == std::string::npos) {
		isBmp = true;
	}
	if (isBmp) {
		surface = SDL_LoadBMP(name);
		if (surface == nullptr) {
			throw SDL_GetError();
		}
		if (SDL_MUSTLOCK(surface)) {
			SDL_LockSurface(surface);
		}
	}
	else {
		ifstream file(name, ios::binary);
		//float f;
		//floats.reserve(size*size*3);
		file.read(reinterpret_cast<char*>(floats.data()), sizeof( float) * 3 * size * size);
		/*while (file.read(reinterpret_cast<char*>(&f), sizeof f)) {
			floats.push_back(f);
		}*/
	}
}

Surface::Surface(Surface && rhs): surface(rhs.surface), floats(std::move(rhs.floats)), isBmp(rhs.isBmp)
{
	rhs.surface = nullptr;
	rhs.floats.clear();
}

Surface & Surface::operator=(Surface && rhs)
{
	if (this != &rhs) {
		free();
		surface = rhs.surface;
		floats = std::move(rhs.floats);
		isBmp = rhs.isBmp;
		size = rhs.size;
	}
	return *this;
}

Surface::~Surface()
{
	free();
}

Color Surface::getColor(Vec3d pos) const
{
	if (isBmp) {
		Vec2d coords;
		coords.x = 0.5 + atan2(pos.z, pos.x) /( 2 * pi());
		coords.y = 0.5 - asin(pos.y) / pi();
		
		coords.x *= surface->w;
		coords.y *= surface->h;
		//note : this bmp is stored in a 24 bit / pixel format.
		//It's possible to query all the necessary format infos using sdl to keep it more general, 
		//but since I'm lazy I'm just gonna make it work for this one format.
		int pos = 3 * (surface->w * static_cast<int>(coords.y) + static_cast<int>(coords.x));
		auto pixel = static_cast<uint8_t*>(surface->pixels) + pos;
		return Color(pixel[0], pixel[1], pixel[2]);
	}
	else {
		double r = (1 / pi())*acos(pos.z) / sqrt(pos.x*pos.x + pos.y*pos.y);
		Vec2d coords = {pos.x * r, -pos.y * r}; 
		coords += {1, 1};
		coords /= 2;
		coords *= size;
		int pos = 3*static_cast<int>(static_cast<int>(coords.y)*size + coords.x);

		
		return Color(floats[pos + 0], floats[pos + 1], floats[pos + 2]);
	}
}

void Surface::free()
{
	if (surface != nullptr) {
		if (SDL_MUSTLOCK(surface)) {
			SDL_UnlockSurface(surface);
		}
		SDL_FreeSurface(surface);
		surface = nullptr;
	}
}
