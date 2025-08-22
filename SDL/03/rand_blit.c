// From 'Focus on SDL' pp. 61-2
#include <SDL/SDL.h>
#include <stdlib.h>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

SDL_Surface* g_pDisplaySurface = NULL;
SDL_Surface* g_pBitmapSurface = NULL;
SDL_Event g_Event;
SDL_Rect g_SrcRect, g_DstRect;

int main(int argc, char* argv[]){
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Could not initialize SDL!\n");
		exit(1);
	} else {
		fprintf(stdout, "SDL initialized properly!\n");
		atexit(SDL_Quit);
	}

	g_pDisplaySurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_ANYFORMAT);
	g_pBitmapSurface = SDL_LoadBMP("ball.bmp");
	g_SrcRect.w = g_DstRect.w = g_pBitmapSurface->w;
	g_SrcRect.h = g_DstRect.h = g_pBitmapSurface->h;
	g_SrcRect.x = g_SrcRect.y = 0;

	for (;;){
		if (SDL_PollEvent(&g_Event) == 0){
			g_DstRect.x = rand()%(SCREEN_WIDTH-g_DstRect.w);
			g_DstRect.y = rand()%(SCREEN_HEIGHT-g_DstRect.h);
			SDL_BlitSurface(g_pBitmapSurface,
					&g_SrcRect,
					g_pDisplaySurface,
					&g_DstRect);
			SDL_UpdateRect(g_pDisplaySurface, 0, 0, 0, 0);
		} else {
			if (g_Event.type == SDL_QUIT){
				break;
			}
		}
	}
}
