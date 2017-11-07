#include "WindowHandle.h"
#include <SDL.h>
#include "Vec2d.h"
#include "Color.h"

WindowHandle::WindowHandle(const Vec2d size):
    window(nullptr),
	surface()
{
	window = SDL_CreateWindow(
		"SDL2 Comgr",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		static_cast<int>(size.x),
		static_cast<int>(size.y),
		0
	);
	if(!window){
		throw SDL_GetError();
	}
	surface = SDL_GetWindowSurface(window);
}


WindowHandle::~WindowHandle()
{
	SDL_DestroyWindow(window);
	window = nullptr;
}


SDL_Window* WindowHandle::get() const{
	return window;
}


Vec2d WindowHandle::getSize() const{
	int x;
	int y;
	SDL_GetWindowSize(window, &x, &y);
	return {static_cast<double>(x), static_cast<double>(y)};
}



void WindowHandle::drawPoint(Vec2d point, Color c) const
{
	static_cast<Uint32*>(surface->pixels)[static_cast<int>(point.y) * surface->w + static_cast<int>(point.x)] = c;
}

void WindowHandle::lock() const{
	if(SDL_MUSTLOCK(surface)){
		SDL_LockSurface(surface);
	}
}

void WindowHandle::unlock() const{
	if(SDL_MUSTLOCK(surface)){
		SDL_UnlockSurface(surface);
	}
	SDL_UpdateWindowSurface(window);
}