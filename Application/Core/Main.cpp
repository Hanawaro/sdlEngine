#include <iostream>
#include <windows.h>

#include "Application.hpp"

#define WIN_WIDTH	800
#define WIN_HEIGHT	600
#define WIN_X_POS	800
#define WIN_Y_POS	190

int main(int argc, char** argv) {

	SDL_Delay(2000);
	{
		Application app("Application", WIN_WIDTH, WIN_HEIGHT, WIN_X_POS, WIN_Y_POS, SDL_WINDOW_SHOWN);
		
		while (app.isRunning()) {
			app.Update();
			app.Render();
			app.HandleEvent();
		}
	}

	return 0;
}