#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

struct Man 
{
	int x, y;
	short life;
	string name;

};


struct GameState 
{
	// Players
	Man man;

	// Texture
	SDL_Texture *star;
};



void doRender(SDL_Renderer *renderer, GameState *game)
{
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		// Load Rect
		SDL_Rect rect = {game->man.x, game->man.y, 50, 50};
		SDL_RenderFillRect(renderer, &rect);

		// Load image
		SDL_Rect starRect = { 50, 50, 64, 64};
		SDL_RenderCopy(renderer, game->star, NULL, &starRect);
		
		

		SDL_RenderPresent(renderer);
}

int processEvents(SDL_Window *window, GameState *game)
{
	SDL_Event event;
	int done = 0;

		while (SDL_PollEvent(&event)) 
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
			    {
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							done = 1;
						break;

					}
				}
				break;
				case SDL_WINDOWEVENT_CLOSE:
				{
					if (window)
					{
						SDL_DestroyWindow(window);
						window = NULL;
						done = 1;
					}
				}
				break;

				case SDL_QUIT:
					done = 1;
				break;
			}
		}
	
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if(state[SDL_SCANCODE_LEFT])
	{
		game->man.x -= 10;
	}
	if(state[SDL_SCANCODE_RIGHT])
	{
		game->man.x += 10;
	}
		if(state[SDL_SCANCODE_DOWN])
	{
		game->man.y += 10;
	}
	if(state[SDL_SCANCODE_UP])
	{
		game->man.y -= 10;
	}
	return done;
}


int main (){

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Surface *starSurface = NULL;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Game Window",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  640,
							  480,
							  0);
	
	if (window == NULL)
    {
        cout << "Error al crear la ventana: " << SDL_GetError() << endl;
        return 1;
    }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
    {
        cout << "Error al crear el renderizador: " << SDL_GetError() << endl;
        return 1;
    }

	GameState gameState;
	gameState.man.x = 320-40;
	gameState.man.y = 240-40;

	starSurface = SDL_LoadBMP("chai.bmp");

	if ( starSurface == NULL)
	{
		cout << "Error al cargar la imagen: " << SDL_GetError() << endl;
		// cout << SDL_GetBasePath() << endl;
		SDL_Quit();
		return 1;
	}

	gameState.star = SDL_CreateTextureFromSurface(renderer, starSurface);
	SDL_FreeSurface(starSurface);

	

	doRender(renderer, &gameState);
	
	int done = 0;
	while(!done)
	{
		
		
		doRender(renderer, &gameState);
		done = processEvents(window, &gameState);

		// Comment Delay because of we use SDL_RENDERER_PRESENTVSYNC
		// SDL_Delay(100);
	}
		
	SDL_DestroyTexture(gameState.star);

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;

}