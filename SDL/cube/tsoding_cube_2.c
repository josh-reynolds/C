// 2D projection of 3D points
// from YouTube video by tsoding
// "One Formula That Demystifies 3D Graphics"
//
// Redoing this project with SDL2
//
// gcc ./tsoding_cube_2.c -o cube2.out -lSDL2 && ./cube2.out

#include <stdbool.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=800;

SDL_Window* g_pScreen = NULL;
SDL_Renderer* g_pRenderer = NULL;

bool is_running = false;

int main(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL.\n");
		exit(1);
	}

	g_pScreen = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_BORDERLESS
			);

	g_pRenderer = SDL_CreateRenderer(g_pScreen, -1, 0);

	is_running = true;

	while(is_running){
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type){
			case SDL_QUIT:
				is_running = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					is_running = false;
				break;
		}

		SDL_SetRenderDrawColor(g_pRenderer, 128, 0, 0, 255);
		SDL_RenderClear(g_pRenderer);
		SDL_RenderPresent(g_pRenderer);
	}

	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pScreen);
	SDL_Quit();
}
