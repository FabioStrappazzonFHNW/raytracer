#include "Context.h"
#include "SDL.h"
#include <iostream>

int main(int argc, char **argv)
{
	try{
		Context x;
		x.loop();
	}catch(const char* error){
		std::cerr<<error;
		return -1;
	}
	return 0;
}
