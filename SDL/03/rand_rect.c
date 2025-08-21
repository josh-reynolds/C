// From 'Focus on SDL' pp. 55-6
#include <SDL/SDL.h>
#include <stdlib.h>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

SDL_Surface* g_pDisplaySurface = NULL;
SDL_Event g_Event;
SDL_Rect g_Rect;
Uint8 g_Red, g_Green, g_Blue;
Uint32 g_Color;

int main(int argc, char* argv[]){
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Could not initialize SDL!\n");
		exit(1);
	} else {
		fprintf(stdout, "SDL initialized properly!\n");
		atexit(SDL_Quit);
	}

	g_pDisplaySurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_ANYFORMAT);

	for (;;){
		if (SDL_PollEvent(&g_Event) == 0){
			g_Red = rand()%256;
			g_Green = rand()%256;
			g_Blue = rand()%256;
			g_Color = SDL_MapRGB(g_pDisplaySurface->format, g_Red,
					g_Green, g_Blue);
			g_Rect.x = rand()%SCREEN_WIDTH;
			g_Rect.y = rand()%SCREEN_HEIGHT;
			g_Rect.w = rand()%(SCREEN_WIDTH - g_Rect.x);
			g_Rect.h = rand()%(SCREEN_HEIGHT - g_Rect.y);
			SDL_FillRect(g_pDisplaySurface, &g_Rect, g_Color);
			SDL_UpdateRect(g_pDisplaySurface, 0, 0, 0, 0);
		} else {
			if (g_Event.type == SDL_QUIT){
				break;
			}
		}
	}
}
