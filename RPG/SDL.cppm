export module engine.SDL;

export namespace sdl {
#include <SDL.h>
	
	namespace image {
#include <SDL_image.h> 
	}

	namespace ttf {
#include <SDL_ttf.h>
	}
}