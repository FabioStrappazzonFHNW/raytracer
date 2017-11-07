#include "RendererHandle.h"
#include <SDL.h>


RendererHandle::RendererHandle(SDL_Window* window):
    renderer(nullptr)
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC); //SDL_RENDERER_ACCELERATED);// 
	if(!renderer){
		throw SDL_GetError();
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}


RendererHandle::~RendererHandle()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
}
SDL_Renderer* RendererHandle::get() const{
	return renderer;
}

void RendererHandle::render() const{
	SDL_RenderPresent(renderer);
}


void RendererHandle::clear() const{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}