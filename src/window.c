//
// Created by pascal on 12.04.26.
//
#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "window.h"

#include "animation.h"

#define THROW_ERROR(MSG, ...) do {		\
	fprintf(stderr, MSG "\n", ##__VA_ARGS__);  \
	return -1;  \
}while (0);

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

void hello_world()
{
	printf("Hello World!\n");
}

int init_app()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) THROW_ERROR("Couldn't init SDL library: %s", SDL_GetError());

	if (! ((window = SDL_CreateWindow("My SDL3 Window Title", 800, 600, SDL_WINDOW_FULLSCREEN))) )
		THROW_ERROR("Cound't create Window: %s", SDL_GetError());

	// Set some specific behavior settings
	SDL_SetWindowBordered(window, false);
	SDL_SetWindowAlwaysOnTop(window, false);

	if (! ((renderer = SDL_CreateRenderer(window, nullptr))) )
		THROW_ERROR("Couldn't create window and renderer: %s", SDL_GetError());

	SDL_SetRenderVSync(renderer, 1);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250);
	SDL_RenderClear(renderer);
	init_particles(renderer);
	SDL_RenderPresent(renderer);
	return 0;
}

int run_app()
{
	int running = 1;
	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (
				/* either */event.type == SDL_EVENT_QUIT
				||
				/* or */	(event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_Q && event.key.mod & SDL_KMOD_LCTRL)
				) running = 0;
		}
		//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250);
		//SDL_RenderClear(renderer);
		//SDL_RenderPresent(renderer);
		SDL_Delay(16);  // ~60FPS
	}
	return 0;
}

int quit_app()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}