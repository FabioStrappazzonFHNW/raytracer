#pragma once
#include <string>
struct SDL_Window;
class Vec2d;
struct SDL_Surface;

class Color;

class WindowHandle
{
public:
	explicit WindowHandle(Vec2d size);
	WindowHandle(const WindowHandle&) = delete;
	WindowHandle& operator=(const WindowHandle&) = delete;
	~WindowHandle();
	
	SDL_Window* get() const;
	Vec2d getSize() const;
	
	void drawPoint(Vec2d point, Color c) const;
	void lock() const;
	void unlock() const;

private:
	SDL_Window* window;
	SDL_Surface* surface;
};

