#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL.h>

struct WindowEntity {
	SDL_Window* window;
	Uint16 width;
	Uint16 height;
};

#endif