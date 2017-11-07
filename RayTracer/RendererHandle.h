#pragma once
class Vec2d;
struct SDL_Renderer;
struct SDL_Window;

class RendererHandle
{
public:
	explicit RendererHandle(SDL_Window* window);
	RendererHandle(const RendererHandle&) = delete;
	RendererHandle& operator=(const RendererHandle&) = delete;
	~RendererHandle();
	
	SDL_Renderer* get() const;
	void render() const;
	void clear() const;

private:
	SDL_Renderer* renderer;
};
