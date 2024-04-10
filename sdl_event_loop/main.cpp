#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

struct Man {
	int x, y;
	short life;
	string name;

};




void doRender(SDL_Renderer *renderer, Man *man)
{
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect rect = {man->x, man->y, 200, 200};
		cout << "Renderizado: "<<man->x << endl;

		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);
}

int processEvents(SDL_Window *window, Man *man)
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
		man->x -= 10;
	}
	if(state[SDL_SCANCODE_RIGHT])
	{
		man->x += 10;
	}
		if(state[SDL_SCANCODE_DOWN])
	{
		man->y += 10;
	}
	if(state[SDL_SCANCODE_UP])
	{
		man->y -= 10;
	}
	return done;
}


int main (){

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	

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

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == NULL)
    {
        cout << "Error al crear el renderizador: " << SDL_GetError() << endl;
        return 1;
    }

	Man man;
	man.x = 220;
	man.y = 140;

	doRender(renderer, &man);
	
	int done = 0;
	while(!done)
	{
		
		done = processEvents(window, &man);
		doRender(renderer, &man);

		SDL_Delay(100);
	}
		
	
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;

}