#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

struct Man {
	int x, y;
	short life;
	string name;

};

int main (int argc, char *argv[]){

	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Game Window",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  640,
							  480,
							  0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rect = {220, 140, 200, 200};

	SDL_RenderFillRect(renderer, &rect);

	SDL_RenderPresent(renderer);


	SDL_Delay(2000);

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;

}