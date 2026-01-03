// 2D projection of 3D points
// from YouTube video by tsoding
// "One Formula That Demystifies 3D Graphics"

#include <SDL/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=800;

SDL_Surface* g_pDisplaySurface = NULL;
SDL_Event g_Event;
Uint32 FOREGROUND;
Uint32 BACKGROUND;
SDL_Rect g_Rect;
SDL_Rect screen;

void clear(){
	SDL_FillRect(g_pDisplaySurface, &screen, BACKGROUND);
}

void point(int x, int y){
	SDL_Rect rect;
	int s = 20;
	rect.x = x;
	rect.y = y;
	rect.w = s;
	rect.h = s;
	SDL_FillRect(g_pDisplaySurface, &rect, FOREGROUND);
}

int main(void){
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Could not initialize SDL!\n");
		exit(1);
	}

	g_pDisplaySurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_ANYFORMAT);

	FOREGROUND = SDL_MapRGB(g_pDisplaySurface->format, 80, 255, 80);
	BACKGROUND = SDL_MapRGB(g_pDisplaySurface->format, 16, 16, 16);

	screen.x = 0;
	screen.y = 0;
	screen.w = SCREEN_WIDTH;
	screen.h = SCREEN_HEIGHT;

	for (;;){
		if (SDL_PollEvent(&g_Event) == 0){
			clear();
			point(100, 100);

			// update surface
			SDL_UpdateRect(g_pDisplaySurface, 0, 0, 0, 0);
		} else {
			if (g_Event.type == SDL_QUIT){
				break;
			}
		}
	}
}

