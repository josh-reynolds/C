// 2D projection of 3D points
// from YouTube video by tsoding
// "One Formula That Demystifies 3D Graphics"
//
// Redoing this project with SDL2
//
// gcc ./tsoding_cube_2.c -o cube2.out -lSDL2 && ./cube2.out

#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=800;

SDL_Window* g_pWindow = NULL;
SDL_Surface* g_pSurface = NULL;

Uint32 FOREGROUND;
Uint32 BACKGROUND;

bool is_running = false;

typedef struct {
	int x, y;
} Point;

void point(Point p){
	SDL_Rect rect;
	int s = 20;
	rect.x = p.x;
	rect.y = p.y;
	rect.w = s;
	rect.h = s;
	SDL_FillRect(g_pSurface, &rect, FOREGROUND);
}

void clear(){
	SDL_FillRect(g_pSurface, NULL, BACKGROUND);
}

int main(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL.\n");
		exit(1);
	}

	g_pWindow = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_BORDERLESS
			);

	g_pSurface = SDL_GetWindowSurface(g_pWindow);
	FOREGROUND = SDL_MapRGB(g_pSurface->format, 80, 255, 80);
	BACKGROUND = SDL_MapRGB(g_pSurface->format, 16, 16, 16);

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

		clear();
		Point p1 = {100, 100};
		point(p1);
		Point p2 = {200, 300};
		point(p2);

		SDL_UpdateWindowSurface(g_pWindow);
	}

	SDL_DestroyWindow(g_pWindow);
	SDL_Quit();
}
