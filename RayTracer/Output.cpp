#include "Output.h"
#include <utility>
#include <SDL_Platform.h>
#include <SDL.h>
#include "WindowHandle.h"
#include "RendererHandle.h"
#include "ResourceHandle.h"
#include "Surface.h"
#include "Vec2d.h"

struct Output::impl{
	
	//order of the following is important
	ResourceHandle sdl {[]{
			if(SDL_Init(SDL_INIT_EVERYTHING)<0){
				throw SDL_GetError();
			}
		},[]{
			SDL_Quit();
		}
	};
	WindowHandle window {{800, 800}};
	RendererHandle renderer {window.get()};
	Surface wall{ "stones.bmp" };
	Surface grace{ "grace_probe.float" , 1'000};
	Surface uffizi{ "uffizi_probe.float" , 1'500};
};

Output& Output::instance(){
    static Output instance;
    return instance;
}
Output::~Output() = default;

Output::Output():
pimpl(std::make_unique<impl>())
{
}




void Output::updateScreen(){
	pimpl->renderer.render();
}



const RendererHandle& Output::getRenderer() const{
	return pimpl->renderer;
}

const WindowHandle& Output::getWindow() const{
	return pimpl->window;
}

const Surface * Output::getWall()
{
	return &(pimpl->wall);
}

const Surface * Output::getGrace()
{
	return &(pimpl->grace);
}

const Surface * Output::getUffizi()
{
	return &(pimpl->uffizi);
}
