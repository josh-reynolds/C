// From 'Focus on SDL' pp. 59-60
#include <SDL/SDL.h>
#include <stdlib.h>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

SDL_Surface* g_pDisplaySurface = NULL;
SDL_Event g_Event;
SDL_Rect g_Rect;
Uint8 g_Red, g_Green, g_Blue;
Uint32 g_x, g_y;
Uint32 g_Color;

void set_pixel(char* pixels, Uint32* color){
	if (SDL_MUSTLOCK(g_pDisplaySurface)) SDL_LockSurface(g_pDisplaySurface);
	memcpy(pixels, &g_Color, g_pDisplaySurface->format->BytesPerPixel);
	if (SDL_MUSTLOCK(g_pDisplaySurface)) SDL_UnlockSurface(g_pDisplaySurface);
}

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

			g_x = rand()%SCREEN_WIDTH;
			g_y = rand()%SCREEN_HEIGHT;

			char* pData;
			pData = (char*)g_pDisplaySurface->pixels;
			pData += (g_y * g_pDisplaySurface->pitch);
			pData += (g_x * g_pDisplaySurface->format->BytesPerPixel);

			set_pixel(pData, &g_Color);

			SDL_UpdateRect(g_pDisplaySurface, 0, 0, 0, 0);
		} else {
			if (g_Event.type == SDL_QUIT){
				break;
			}
		}
	}
}
