// From 'Focus on SDL' pp. 69
#include <SDL/SDL.h>
#include <stdlib.h>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

SDL_Event g_Event;
SDL_Surface* g_pDisplaySurface = NULL;
SDL_Color g_PaletteColors[256];

int main(int argc, char* argv[]){
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Could not initialize SDL!\n");
		exit(1);
	} else {
		fprintf(stdout, "SDL initialized properly!\n");
		atexit(SDL_Quit);
	}

	g_pDisplaySurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 8, SDL_HWPALETTE);

	int index;
	for (index = 0; index < 256; index++){
		g_PaletteColors[index].r = index;
		g_PaletteColors[index].g = index;
		g_PaletteColors[index].b = index;
	}

	SDL_SetColors(g_pDisplaySurface, g_PaletteColors, 0, 256);

	for (;;){
		if (SDL_PollEvent(&g_Event) == 0){
			SDL_Rect FillRect;
			for (index = 0; index < 256; index++){
				FillRect.x = index;
				FillRect.y = index;
				FillRect.w = SCREEN_WIDTH - index;
				FillRect.h = SCREEN_HEIGHT - index;
				SDL_FillRect(g_pDisplaySurface, &FillRect, index);
			}

			SDL_UpdateRect(g_pDisplaySurface, 0, 0, 0, 0);
		} else {
			if (g_Event.type == SDL_QUIT){
				break;
			}
		}
	}
}
