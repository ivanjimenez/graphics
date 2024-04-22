#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "timer.h"

const int window_width = 640, window_height = 480;

// Clear color buffer

void clear_color_buffer(uint32_t color, uint32_t *color_buffer)
{
    for (size_t y = 0; y < window_height; y++)
    {
        for (size_t x = 0; x < window_width; x++)
        {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

// Draa a grid with given

void draw_grid(uint32_t color, uint32_t *color_buffer)
{
    for (size_t y = 0; y < window_height; y += 10)
    {
        for (size_t x = 0; x < window_width; x += 10)
        {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

// Draw rectangle
void draw_rect(int sx, int sy, int width, int height, uint32_t *color_buffer, uint32_t color)
{
    for (size_t y = sy; (y < sy + height) && (y < window_height); y++)
    {
        for (size_t x = sx; (x < sx + width) && (x < window_width); x++)
        {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

int main(int argc, char *argv[])
{
	Timer fpsTimer;
	
	Timer t = Timer();

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	uint32_t *color_buffer = NULL;
	SDL_Texture *color_buffer_texture = NULL;

	SDL_Surface *text;
	TTF_Font *font;
	SDL_Color color = {255, 0, 0};

	// Cálculo de FPS
	int countedFrames = 0;
	float avgFPS = 0;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Hello SDL WORLD", 
										  SDL_WINDOWPOS_UNDEFINED, 
										  SDL_WINDOWPOS_UNDEFINED, 
										  window_width, 
										  window_height, 
										  SDL_WINDOW_ALLOW_HIGHDPI);

    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if ( renderer == NULL)
	{
		std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
        return 1;
	}

	color_buffer = static_cast<uint32_t *>(malloc(sizeof(uint32_t) * window_width * window_height));

	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);

	if ( color_buffer_texture == NULL)
	{
		std::cout << "Could not create texture: " << SDL_GetError() << std::endl;
        return 1;
	}
	
	if (TTF_Init() < 0)
	{
		std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}

	// font setup
	font = TTF_OpenFont("assets/FreeSans.ttf", 16);
	if (!font)
	{
		std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		return false;
	}


	text = TTF_RenderText_Solid(font, (std::to_string(avgFPS) + " fps").c_str(), color);
	if (!text)
	{
		std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
	}
	
	SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_Event windowEvent;

	fpsTimer.start();

	Timer capTimer;

    while (true)
    {
	
		// Render
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

		SDL_RenderClear(renderer);

		clear_color_buffer((uint32_t) 0xFFFFFFFF, color_buffer);

		draw_grid((uint32_t) 0x7777777A, color_buffer);
		
		draw_rect(50, 50, 60, 60, color_buffer, 0x12345678);
		draw_rect(50, 150, 60, 60, color_buffer, 0x12345611);

		// Necessary to render
		SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, window_width * sizeof(uint32_t));
    	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);

		// Calcular los FPS medios
		avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		++countedFrames;
		// Poner el texto sólido
		text = TTF_RenderText_Solid(font, (std::to_string(avgFPS) + " fps").c_str(), color);
		
		// Crear la textura a partir de la superficie de texto
		text_texture = SDL_CreateTextureFromSurface(renderer, text);
		if (text_texture == nullptr) {
			std::cerr << "Error al crear la textura de texto: " << SDL_GetError() << std::endl;
		}

		// Renderizar la textura en la ventana
		SDL_Rect dest = {2, 459, text->w, text->h};
		SDL_RenderCopy(renderer, text_texture, NULL, &dest);
		
		// Liberar la textura creada
		SDL_DestroyTexture(text_texture); 

		// Liberar la superficie de texto
		SDL_FreeSurface(text);
		
		// Presentar el renderer
		SDL_RenderPresent(renderer);
			

        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }


    }

	
	// Cerrar al destruir la ventana
	TTF_CloseFont(font);
	TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}